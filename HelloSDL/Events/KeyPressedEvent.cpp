#include "KeyPressedEvent.h"

KeyPressedEvent::KeyPressedEvent(SDL_KeyboardEvent *input) : EventObject(type)
{
	this->input = input;
}


KeyPressedEvent::~KeyPressedEvent(void)
{
}
