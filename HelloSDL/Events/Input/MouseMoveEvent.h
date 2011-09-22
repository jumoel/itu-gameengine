#pragma once
#include "eventobject.h"
#include "SDL_events.h"
class MouseMoveEvent :
	public EventObject
{
public:
	MouseMoveEvent(SDL_MouseMotionEvent *input, short eventtype);
	~MouseMoveEvent(void);

private:
	SDL_MouseMotionEvent *input;
};

