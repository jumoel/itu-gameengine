#ifndef ITUENGINE_MOUSECLICKEVENT_H
#define ITUENGINE_MOUSECLICKEVENT_H

#include <SDL_events.h>
#include <Events/EventObject.hpp>
#include <Macros/EventMacros.hpp>
#include <iostream>

class MouseClickEvent :
	public EventObject
{
public:
	MouseClickEvent(SDL_MouseButtonEvent *input, short eventtype);
	~MouseClickEvent(void);

	SDL_MouseButtonEvent* GetInput();
	void TestPrint();

private:
	SDL_MouseButtonEvent *input;
};

class IMouseClickEvent
{
	DECLARE_EVENT_INTERFACE(IMouseClickEvent);
public:
	DEFINE_1_ARG_EVENT(IMouseClickEvent, ButtonDown, MouseClickEvent*);
	DEFINE_1_ARG_EVENT(IMouseClickEvent, ButtonUp, MouseClickEvent*);
};
IMPLEMENT_EVENT_INTERFACE(IMouseClickEvent);

#endif