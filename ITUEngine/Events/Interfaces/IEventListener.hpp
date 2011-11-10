#ifndef ITUENGINE_IEVENTLISTENER_H
#define ITUENGINE_IEVENTLISTENER_H

#include <Events/Interfaces/IEventData.hpp>

class IEventListener
{
public:
	explicit IEventListener() {}

	virtual ~IEventListener() {}

	//Returns the name of the listener, for debugging.
	virtual char const * GetName(void) = 0;

	// Return 'false' to indicate that this listener did NOT
	// consume the event, ( and it should continue to be
	// propagated )				
	// return 'true' to indicate that this listener consumed the
	// event, ( and it should NOT continue to be propagated )
	virtual bool HandleEvent( IEventData const & event ) = 0;
};

#endif //ITUENGINE_IEVENTLISTENER_H