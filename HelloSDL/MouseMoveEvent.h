#pragma once
#include "eventobject.h"
#include "SDL_events.h"
class MouseMoveEvent :
	public EventObject
{
public:
	MouseMoveEvent(SDL_MouseMotionEvent *input);
	~MouseMoveEvent(void);

private:
	SDL_MouseMotionEvent *input;
};

