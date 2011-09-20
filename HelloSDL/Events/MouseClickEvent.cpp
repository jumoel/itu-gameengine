#include "MouseClickEvent.h"


MouseClickEvent::MouseClickEvent(SDL_MouseButtonEvent *input) : EventObject(type)
{
	this->input = input;
}


MouseClickEvent::~MouseClickEvent(void)
{
}
