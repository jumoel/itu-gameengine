#ifndef ITUENGINE_EVENTMANAGER_H
#define ITUENGINE_EVENTMANAGER_H

#include <Events/Interfaces/IEventManager.hpp>

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
	virtual bool ProcessEventQueue ( unsigned long maxMillis = -1 );

	virtual bool ValidateType( EventType const & inType ) const;
};

#endif //ITUENGINE_EVENTMANAGER_H

