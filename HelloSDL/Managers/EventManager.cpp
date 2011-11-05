#include <Managers/EventManager.hpp>


EventManager::EventManager(char const * const pName, bool setAsGlobal) : IEventManager(pName, setAsGlobal)
{

}

EventManager::~EventManager()
{
}

bool EventManager::AddListener ( EventListenerPointer const & inHandler, EventType const & inType )
{
	return true;
}

bool EventManager::DelListener ( EventListenerPointer const & inHandler, EventType const & inType )
{
	return true;
}

bool EventManager::TriggerEvent ( IEventData const & inEvent ) const
{
	return true;
}

bool EventManager::QueueEvent ( IEventDataPointer const & inEvent )
{
	return true;
}

bool EventManager::ThreadSafeQueueEvent ( IEventDataPointer const & inEvent )
{
	return true;
}

bool EventManager::AbortEvent ( EventType const & inType, bool allOfType )
{
	return true;
}

//Can be set to stop processing after maxMillis, default is no limit.
bool EventManager::ProcessEventQueue ( unsigned long maxMillis )
{
	return true;
}

bool EventManager::ValidateType( EventType const & inType ) const
{
	return true;
}
