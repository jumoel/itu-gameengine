#pragma once
#include "mouseevent.h"
class MouseMoveEvent :
	public EventObject
{
public:
	MouseMoveEvent(SDL_MouseMotionEvent *input);
	~MouseMoveEvent(void);

private:
	SDL_MouseMotionEvent *input;
};

