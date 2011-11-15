#include <Events/Interfaces/IEventManager.hpp>
#include <Events/Interfaces/IEventListener.hpp>
#include <assert.h>
#include <tchar.h>


static IEventManager * globalEventManagerInstance = NULL;

IEventManager * IEventManager::Instance()
{
	return globalEventManagerInstance;
}

void IEventManager::StartUp( char const * const pName, bool setAsGlobal )
{
	if ( setAsGlobal )
	{
		globalEventManagerInstance = this;
	}
}

void IEventManager::ShutDown()
{
	if ( globalEventManagerInstance == this )
	{
		globalEventManagerInstance = NULL;
	}
}

// safe function which will catch non-ready system calls to the global manager.
bool safeAddListener( EventListenerPointer const & inHandler, EventType const & inType )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->AddListener( inHandler, inType );
}

bool safeDelListener( EventListenerPointer const & inHandler, EventType const & inType )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->DelListener( inHandler, inType );
}

bool safeTriggerEvent( IEventData const & inEvent )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->TriggerEvent( inEvent );
}

bool safeQueEvent( IEventDataPointer const & inEvent )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->QueueEvent( inEvent );
}

bool threadSafeQueEvent ( IEventDataPointer const & inEvent )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->ThreadSafeQueueEvent( inEvent );
}

bool safeAbortEvent( EventType const & inType, bool allOfType /* = false */ )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->AbortEvent( inType, allOfType );
}

bool safeTickEventManager( unsigned long maxMillis /* = -1 */ )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->ProcessEventQueue( maxMillis );
}

bool safeValidateEventType( EventType const & inType )
{
	assert(IEventManager::Instance() && _T("No event manager!"));
	return IEventManager::Instance()->ValidateType( inType );
}