#include <Managers/EventManager.hpp>
#include <Abstractions/Time.hpp>
#include <assert.h>

void EventManager::StartUp(char const * const pName, bool setAsGlobal)
{
	IEventManager::StartUp(pName, setAsGlobal);
	m_activeQueue = 0;

	AddRegisteredEventType( wildcardEventType );
	AddRegisteredEventType( EventType("keydownEvent") );
}

void EventManager::ShutDown()
{
	IEventManager::ShutDown();
	m_activeQueue = 0;
}

bool EventManager::AddListener ( EventListenerPointer const & inHandler, EventType const & inType )
{
	if ( ! ValidateType( inType ) )
		return false;

	// check / update type list

	EventTypeSet::iterator eventTypeIterator = m_typeList.find( inType );

	// find listener map entry, create one if no table already
	// exists for this entry ...

	EventListenerMap::iterator eventListenerMapIterator =
		m_registry.find( inType.GetHashValue() );

	if ( eventListenerMapIterator == m_registry.end() )
	{
		EventListenerMapIRes elmIRes = m_registry.insert(
			EventListenerMapEnt( inType.GetHashValue(),
			EventListenerTable() ) );

		// whoops, could not insert into map!?!?
		if ( elmIRes.second == false )
			return false;

		// should not be possible, how did we insert and create
		// an empty table!?!?!
		if ( elmIRes.first == m_registry.end() )
			return false;

		// store it so we can update the mapped list next ...
		eventListenerMapIterator = elmIRes.first;
	}

	// update the mapped list of listeners, walk the existing
	// list (if any entries) to prevent duplicate addition of
	// listeners. This is a bit more costly at registration time
	// but will prevent the hard-to-notice duplicate event
	// propagation sequences that would happen if double-entries
	// were allowed.

	// note: use reference to make following code more simple
	EventListenerTable & evlTable = (*eventListenerMapIterator).second;

	for ( EventListenerTable::iterator it = evlTable.begin(),
		itEnd = evlTable.end(); it != itEnd ; it++ )
	{
		bool bListenerMatch = ( *it == inHandler );

		if ( bListenerMatch )
			return false;
	}

	// event type validated, event listener validated,
	// event listener not already in map, add it

	evlTable.push_back( inHandler );

	return true;
}

bool EventManager::DelListener ( EventListenerPointer const & inHandler, EventType const & inType )
{
	if ( ! ValidateType( inType ) )
		return false;

	bool rc = false;

	// brute force method, iterate through all existing mapping
	// entries looking for the matching listener and remove it.

	for ( EventListenerMap::iterator it = m_registry.begin(),
		itEnd = m_registry.end(); it != itEnd; it++ )
	{
		unsigned int const    kEventId = it->first;
		EventListenerTable & table    = it->second;

		for ( EventListenerTable::iterator it2 = table.begin(),
			it2End = table.end(); it2 != it2End; it2++ )
		{
			if ( *it2 == inHandler )
			{
				// found match, remove from table,
				table.erase( it2 );

				// update return code
				rc = true;

				// and early-quit the inner loop as addListener()
				// code ensures that each listener can only
				// appear in one event's processing list once.
				break;
			}
		}
	}

	return rc;
}

bool EventManager::TriggerEvent ( IEventData const & inEvent ) const
{
	if ( ! ValidateType( inEvent.GetEventType() ) )
		return false;

	EventListenerMap::const_iterator itWC = m_registry.find( 0 );

	if ( itWC != m_registry.end() )
	{
		EventListenerTable const & table = itWC->second;

		bool processed = false;

		for ( EventListenerTable::const_iterator it2 = table.begin(),
			it2End = table.end(); it2 != it2End; it2++ )
		{
			(*it2)->HandleEvent( inEvent );
		}
	}

	EventListenerMap::const_iterator it =
		m_registry.find( inEvent.GetEventType().GetHashValue() );

	if ( it == m_registry.end() )
		return false;

	EventListenerTable const & table = it->second;

	bool processed = false;

	for ( EventListenerTable::const_iterator it2 = table.begin(),
		it2End = table.end(); it2 != it2End; it2++ )
	{
		EventListenerPointer listener = *it2;
		if ( listener->HandleEvent( inEvent ) )
		{
			// only set to true, if processing eats the messages
			processed = true;
		}
	}

	return processed;
}

bool EventManager::QueueEvent ( IEventDataPointer const & inEvent )
{
	assert ( m_activeQueue >= 0 );
	assert ( m_activeQueue < kNumQueues );

	if ( ! ValidateType( inEvent->GetEventType() ) )
		return false;

	EventListenerMap::const_iterator it =
		m_registry.find( inEvent->GetEventType().GetHashValue() );

	if ( it == m_registry.end() )
	{		
		// if global listener is not active, then abort queue add
		EventListenerMap::const_iterator itWC = m_registry.find( 0 );

		if ( itWC == m_registry.end() )
		{
			// no listeners for this event, skip it
			return false;
		}
	}

	m_queues[m_activeQueue].push_back( inEvent );

	return true;
}

bool EventManager::ThreadSafeQueueEvent ( IEventDataPointer const & inEvent )
{
	m_RealtimeEventQueue.push(inEvent);
	return true;
}

bool EventManager::AbortEvent ( EventType const & inType, bool allOfType )
{
	assert ( m_activeQueue >= 0 );
	assert ( m_activeQueue < kNumQueues );

	if ( ! ValidateType( inType ) )
		return false;

	EventListenerMap::iterator it = m_registry.find( inType.GetHashValue() );

	if ( it == m_registry.end() )
		return false; // no listeners for this event, skip it

	bool rc = false;

	EventQueue &evtQueue = m_queues[m_activeQueue];

	for ( EventQueue::iterator it = evtQueue.begin(),
		itEnd = evtQueue.end(); it != itEnd; it++ )
	{
		if ( (*it)->GetEventType() == inType )
		{
			it = evtQueue.erase(it);
			rc = true;
			if ( !allOfType )
				break;
		}
		else
		{
			++it;
		}
	}

	return rc;
}

//Can be set to stop processing after maxMillis, default is no limit.
bool EventManager::ProcessEventQueue ( unsigned long maxMillis )
{
	unsigned long curMs = Time::GetCurrentMS();
	unsigned long maxMs = maxMillis == IEventManager::INFINITE ? IEventManager::INFINITE : (curMs + maxMillis );

	EventListenerMap::const_iterator itWC = m_registry.find( 0 );

	// This section added to handle events from other threads
	// Check out Chapter 18
	// --------------------------------------------------------
	IEventDataPointer rte;

	while (m_RealtimeEventQueue.try_pop(rte))
	{
		QueueEvent(rte);

		curMs = Time::GetCurrentMS();
		if ( maxMillis != IEventManager::INFINITE )
		{
			if ( curMs >= maxMs )
			{
				assert(0 && "A realtime process is spamming the event manager!");
			}
		}
	}
	// --------------------------------------------------------

	// swap active queues, make sure new queue is empty after the swap
	int queueToProcess = m_activeQueue;

	m_activeQueue = ( m_activeQueue + 1 ) % kNumQueues;

	m_queues[m_activeQueue].clear();

	// now process as many events as we can ( possibly time
	// limited ) ... always do AT LEAST one event, if ANY are
	// available ...

	while ( m_queues[queueToProcess].size() > 0 )
	{
		IEventDataPointer event = m_queues[queueToProcess].front();

		m_queues[queueToProcess].pop_front();

		EventType const & eventType = event->GetEventType();

		EventListenerMap::const_iterator itListeners = m_registry.find( eventType.GetHashValue() );

		if ( itWC != m_registry.end() )
		{
			EventListenerTable const & table = itWC->second;

			bool processed = false;

			for ( EventListenerTable::const_iterator it2 = table.begin(), it2End = table.end(); it2 != it2End; it2++ )
			{
				(*it2)->HandleEvent( *event );
			}
		}

		// no listeners currently for this event type, skip it
		if ( itListeners == m_registry.end() )
			continue;

		unsigned int const kEventId = itListeners->first;
		EventListenerTable const & table = itListeners->second;

		for ( EventListenerTable::const_iterator it = table.begin(), end = table.end(); it != end ; it++ )
		{
			if ( (*it)->HandleEvent( *event ) )
			{
				break;
			}
		}

		curMs = Time::GetCurrentMS();

		if ( maxMillis != IEventManager::INFINITE )
		{
			if ( curMs >= maxMs )
			{
				// time ran about, abort processing loop
				break;
			}
		}
	}

	// if any events left to process, push them onto the active
	// queue.
	//
	// Note: to preserver sequencing, go bottom-up on the
	// reminder, inserting them at the head of the active
	// queue...

	bool queueFlushed = ( m_queues[queueToProcess].size() == 0 );

	if ( !queueFlushed )
	{
		while ( m_queues[queueToProcess].size() > 0 )
		{
			IEventDataPointer event = m_queues[queueToProcess].back();

			m_queues[queueToProcess].pop_back();

			m_queues[m_activeQueue].push_front( event );
		}
	}

	return queueFlushed;
}

bool EventManager::ValidateType( EventType const & inType ) const
{
	if ( 0 == inType.GetString().length() )
		return false;

	if ( ( inType.GetHashValue() == 0 ) && (strcmp(inType.GetString().c_str(), wildcardEventType.GetString().c_str()) != 0) )
		return false;

	EventTypeSet::const_iterator evIt = m_typeList.find( inType );

	if ( evIt == m_typeList.end() )
	{
		assert( 0 && "Failed validation of an event type; it was probably not registered with the EventManager!" );
		return false;
	}

	return true;
}

void EventManager::AddRegisteredEventType( const EventType & eventType )
{
	const EventTypeSet::const_iterator iter = m_typeList.find( eventType );
	if ( iter == m_typeList.end() )
	{
		// insert the new event type
		m_typeList.insert( std::make_pair( eventType, IRegisteredEvent::CodeEventOnly ) );
	}
}