#include "EventObject.h"


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

