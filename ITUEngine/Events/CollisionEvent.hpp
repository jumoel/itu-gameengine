#ifndef ITUENGINE_COLLISIONEVENT_H
#define ITUENGINE_COLLISIONEVENT_H

#include <Events/EventObject.hpp>

class CollisionEvent :
	public EventObject
{
public:
	CollisionEvent(short eventtype);
	~CollisionEvent(void);
};

#endif

