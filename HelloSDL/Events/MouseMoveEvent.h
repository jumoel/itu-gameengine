#ifndef ITUENGINE_MOUSEMOVEEVENT_H
#define ITUENGINE_MOUSEMOVEEVENT_H

#include "EventObject.h"
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

#endif
