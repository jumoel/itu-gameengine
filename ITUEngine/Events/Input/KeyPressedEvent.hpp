#ifndef ITUENGINE_KEYPRESSEDEVENT_H
#define ITUENGINE_KEYPRESSEDEVENT_H

#include <SDL_events.h>
#include <Events/EventObject.hpp>
#include <Macros/EventMacros.hpp>
#include <iostream>

class KeyPressedEvent :
	public EventObject
{
public:
	KeyPressedEvent(SDL_KeyboardEvent *input, short eventtype);
	~KeyPressedEvent(void);

	SDL_KeyboardEvent* GetInput();
	void TestPrint();

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