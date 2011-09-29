#ifndef ITUENGINE_MOUSEMOVEEVENT_H
#define ITUENGINE_MOUSEMOVEEVENT_H

#include "../EventObject.h"
#include "SDL_events.h"
#include "../../Macros/EventMacros.h"

class MouseMoveEvent :
	public EventObject
{
public:
	MouseMoveEvent(SDL_MouseMotionEvent *input, short eventtype);
	~MouseMoveEvent(void);

	SDL_MouseMotionEvent* GetInput();

private:
	SDL_MouseMotionEvent *input;
};

class IMouseMoveEvent
{
	DECLARE_EVENT_INTERFACE(IMouseMoveEvent);
public:
	DEFINE_1_ARG_EVENT(IMouseMoveEvent, Motion, MouseMoveEvent*);
};
IMPLEMENT_EVENT_INTERFACE(IMouseMoveEvent);


#endif
