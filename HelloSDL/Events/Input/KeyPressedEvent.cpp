#include "KeyPressedEvent.h"

KeyPressedEvent::KeyPressedEvent(SDL_KeyboardEvent *input, short eventtype) : EventObject(eventtype)
{
	this->input = input;
}


KeyPressedEvent::~KeyPressedEvent(void)
{
}
