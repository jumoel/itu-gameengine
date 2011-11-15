#ifndef ITUENGINE_MOUSEMOVEEVENT_H
#define ITUENGINE_MOUSEMOVEEVENT_H

#include <SDL_events.h>
#include <Events/EventObject.hpp>
#include <Macros/EventMacros.hpp>
#include <iostream>

class MouseMoveEvent :
	public EventObject
{
public:
	MouseMoveEvent(SDL_MouseMotionEvent *input, short eventtype);
	~MouseMoveEvent(void);

	SDL_MouseMotionEvent* GetInput();
	void TestPrint();

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