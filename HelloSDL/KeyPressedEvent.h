#pragma once
#include "EventObject.h"
#include "SDL_events.h"

class KeyPressedEvent :
	public EventObject
{
public:
	KeyPressedEvent(SDL_KeyboardEvent *input);
	~KeyPressedEvent(void);

private:
	SDL_KeyboardEvent *input;
};

