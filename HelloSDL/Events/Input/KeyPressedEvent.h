#ifndef ITUENGINE_KEYPRESSEDEVENT_H
#define ITUENGINE_KEYPRESSEDEVENT_H

#include "../eventobject.h"
#include "SDL_events.h"
#include "../../Macros/EventMacros.h"

class KeyPressedEvent :
	public EventObject
{
public:
	KeyPressedEvent(SDL_KeyboardEvent *input, short eventtype);
	~KeyPressedEvent(void);

	SDL_KeyboardEvent* GetInput();

private:
	SDL_KeyboardEvent *input;
};

class IKeyboardEvent
{
	DECLARE_EVENT_INTERFACE(IKeyboardEvent);
public:
	DEFINE_1_ARG_EVENT(IKeyboardEvent, KeyDown, KeyPressedEvent*);
	DEFINE_1_ARG_EVENT(IKeyboardEvent, KeyUp, KeyPressedEvent*);
};
IMPLEMENT_EVENT_INTERFACE(IKeyboardEvent);

#endif
