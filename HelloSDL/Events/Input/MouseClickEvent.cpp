#include "MouseClickEvent.h"


MouseClickEvent::MouseClickEvent(SDL_MouseButtonEvent *input, short eventtype) : EventObject(eventtype)
{
	this->input = input;
}


MouseClickEvent::~MouseClickEvent(void)
{
}
