#pragma once
#include "Events\Input\KeyPressedEvent.h"
#include "Events\Input\MouseClickEvent.h"

class TestEventSubscribtion : public IKeyboardEvent, public IMouseClickEvent
{
protected:
	void OnKeyDown(KeyPressedEvent *key);
	void OnKeyUp(KeyPressedEvent *key);
	
	void OnButtonDown(MouseClickEvent *button);

public:
	TestEventSubscribtion(void);
	~TestEventSubscribtion(void);

	
};

