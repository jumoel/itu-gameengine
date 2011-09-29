#pragma once
#include "Events\Input\KeyPressedEvent.h"
#include "Events\Input\MouseClickEvent.h"
#include "Events\Input\MouseMoveEvent.h"

class TestEventSubscribtion : public IKeyboardEvent, public IMouseClickEvent, public IMouseMoveEvent
{
protected:
	void OnKeyDown(KeyPressedEvent *key);
	void OnKeyUp(KeyPressedEvent *key);
	
	void OnButtonDown(MouseClickEvent *button);

	void OnMotion(MouseMoveEvent *motion);
public:
	TestEventSubscribtion(void);
	~TestEventSubscribtion(void);

};

