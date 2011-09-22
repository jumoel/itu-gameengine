#ifndef ITUENGINE_KEYPRESSEDEVENT_H
#define ITUENGINE_KEYPRESSEDEVENT_H

#include "../eventobject.h"
#include "SDL_events.h"

class KeyPressedEvent :
	public EventObject
{
public:
	KeyPressedEvent(SDL_KeyboardEvent *input, short eventtype);
	~KeyPressedEvent(void);

private:
	SDL_KeyboardEvent *input;
};

#endif
