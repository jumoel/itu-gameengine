#pragma once
#include "EventObject.h"
#include "SDL_events.h"

class MouseClickEvent :
	public EventObject
{
public:
	MouseClickEvent(SDL_MouseButtonEvent *input);
	~MouseClickEvent(void);

private:
	SDL_MouseButtonEvent *input;
};

