#include "KeyPressedEvent.h"

KeyPressedEvent::KeyPressedEvent(SDL_KeyboardEvent *input)
{
	this->input = input;
}


KeyPressedEvent::~KeyPressedEvent(void)
{
}
