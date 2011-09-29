#ifndef ITUENGINE_MOUSECLICKEVENT_H
#define ITUENGINE_MOUSECLICKEVENT_H

#include "../EventObject.h"
#include "SDL_events.h"
#include "../../Macros/EventMacros.h"

class MouseClickEvent :
	public EventObject
{
public:
	MouseClickEvent(SDL_MouseButtonEvent *input, short eventtype);
	~MouseClickEvent(void);

	SDL_MouseButtonEvent* GetInput();

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