#include "MouseClickEvent.h"


MouseClickEvent::MouseClickEvent(SDL_MouseButtonEvent *input)
{
	this->input = input;
}


MouseClickEvent::~MouseClickEvent(void)
{
}
