#ifndef ITUENGINE_IEVENTMANAGER_H
#define ITUENGINE_IEVENTMANAGER_H

#include <Events/Interfaces/IEventData.hpp>
#include <Events/Interfaces/IEventListener.hpp>
#include <memory>

typedef std::shared_ptr<IEventListener> EventListenerPointer;

class IEventManager
{
public:

	explicit IEventManager( char const * const pName, bool setAsGlobal );

	virtual ~IEventManager();

	virtual bool AddListener ( EventListenerPointer const & inHandler, EventType const & inType ) = 0;

	virtual bool DelListener ( EventListenerPointer const & inHandler, EventType const & inType ) = 0;

	virtual bool TriggerEvent ( IEventData const & inEvent ) const = 0;

	virtual bool QueueEvent ( IEventDataPointer const & inEvent ) = 0;
	virtual bool ThreadSafeQueueEvent ( IEventDataPointer const & inEvent ) = 0;

	virtual bool AbortEvent ( EventType const & inType, bool allOfType = false ) = 0;

	//Can be set to stop processing after maxMillis, default is no limit.
	virtual bool ProcessEventQueue ( unsigned long maxMillis = -1 ) = 0;

	virtual bool ValidateType( EventType const & inType ) const = 0;

private:

	//Internal function to get the global instance.
	static IEventManager * Get();

	friend bool safeAddListener( EventListenerPointer const & inHandler, EventType const & inType );

	friend bool safeDelListener( EventListenerPointer const & inHandler, EventType const & inType );

	friend bool safeTriggerEvent( IEventData const & inEvent );

	friend bool safeQueueEvent( IEventDataPointer const & inEvent );
	friend bool threadSafeQueueEvent( IEventDataPointer const & inEvent );

	friend bool safeAbortEvent( EventType const & inType, bool allOfType = false );

	friend bool safeTickEventManager( unsigned long maxMillis = -1 );

	friend bool safeValidateEventType( EventType const & inType );
};

//Easy access methods used for access to the global instance
bool safeAddListener( EventListenerPointer const & inHandler, EventType const & inType );

bool safeDelListener( EventListenerPointer const & inHandler, EventType const & inType );

bool safeTriggerEvent( IEventData const & inEvent );

bool safeQueueEvent( IEventDataPointer const & inEvent );
bool threadSafeQueueEvent( IEventDataPointer const & inEvent );

bool safeAbortEvent( EventType const & inType, bool allOfType = false );

bool safeTickEventManager( unsigned long maxMillis = -1 );

bool safeValidateEventType( EventType const & inType );

#endif //ITUENGINE_IEVENTMANAGER_H