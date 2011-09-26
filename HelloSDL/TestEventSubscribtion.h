#pragma once
#include "events\input\keypressedevent.h"

class TestEventSubscribtion : public IKeyboardEvent
{
protected:
	void OnKeyDown(KeyPressedEvent *key);
	void OnKeyUp(KeyPressedEvent *key);

public:
	TestEventSubscribtion(void);
	~TestEventSubscribtion(void);

	
};

