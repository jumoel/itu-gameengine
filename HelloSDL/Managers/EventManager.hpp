#ifndef ITUENGINE_EVENTMANAGER_H
#define ITUENGINE_EVENTMANAGER_H

#include <Events/Interfaces/IEventManager.hpp>
#include <Utils/ThreadSafeEventQueue.hpp>
#include <map>
#include <list>

class EventManager : public IEventManager
{
public:
	explicit EventManager(char const * const pName, bool setAsGlobal);
	virtual ~EventManager();

	virtual bool AddListener ( EventListenerPointer const & inHandler, EventType const & inType );

	virtual bool DelListener ( EventListenerPointer const & inHandler, EventType const & inType );

	virtual bool TriggerEvent ( IEventData const & inEvent ) const;

	virtual bool QueueEvent ( IEventDataPointer const & inEvent );
	virtual bool ThreadSafeQueueEvent ( IEventDataPointer const & inEvent );

	virtual bool AbortEvent ( EventType const & inType, bool allOfType = false );

	//Can be set to stop processing after maxMillis, default is no limit.
	virtual bool ProcessEventQueue ( unsigned long maxMillis = INFINITE );

	virtual bool ValidateType( EventType const & inType ) const;

	//Verifies that such an event does not already exist, then registers it.
	void AddRegisteredEventType( const EventType & eventType );

private:
	class IRegisteredEvent
	{
	public:
		//Meta data about the type and usage of this event.
		enum EventMetaDataType
		{
			// Event is defined in script.
			ScriptDefined,

			//Event is defined by code, and is *NOT* callable from script.
			CodeEventOnly,

			//Event is defined by code, but is callable from script.
			CodeEventScriptCallable,
		};

		IRegisteredEvent( const EventMetaDataType metaData )
			: m_MetaData( metaData )
		{
		}

		virtual ~IRegisteredEvent()
		{
		}

		EventMetaDataType GetEventMetaData( void ) const
		{
			return m_MetaData;
		}
	private:
		const EventMetaDataType m_MetaData;
	};

	// one global instance
	typedef std::map< EventType, IRegisteredEvent >			EventTypeSet;

	// insert result into event type set
	typedef std::pair< EventTypeSet::iterator, bool >		EventTypeSetIRes;

	// one list per event type ( stored in the map )
	typedef std::list< EventListenerPointer >				EventListenerTable;

	// mapping of event identity to listener list
	typedef std::map< unsigned int, EventListenerTable >	EventListenerMap;

	// entry in the event listener map
	typedef std::pair< unsigned int, EventListenerTable >	EventListenerMapEnt;

	// insert result into listener map
	typedef std::pair< EventListenerMap::iterator, bool >	EventListenerMapIRes;

	// queue of pending- or processing-events
	typedef std::list< IEventDataPointer >					EventQueue;

	enum eConstants
	{
		kNumQueues = 2
	};

	EventTypeSet     m_typeList;           // list of registered
	// event types

	EventListenerMap m_registry;           // mapping of event types
	// to listeners

	EventQueue       m_queues[kNumQueues]; // event processing queue,
	// double buffered to
	// prevent infinite cycles

	int               m_activeQueue;        // valid denoting which
	// queue is actively
	// processing, en-queuing
	// events goes to the
	// opposing queue

	ThreadSafeEventQueue m_RealtimeEventQueue;
};

#endif //ITUENGINE_EVENTMANAGER_H

