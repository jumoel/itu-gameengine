#include <Events/EventObject.hpp>

EventObject::EventObject(short type)
{
	this->type = type;
}


EventObject::~EventObject(void)
{
}

short EventObject::GetType()
{
	return type;
}

