#ifndef ITUENGINE_TESTEVENTSUBSCRIBTION_H
#define ITUENGINE_TESTEVENTSUBSCRIBTION_H

#include <Events/Input/KeyPressedEvent.hpp>
#include <Events/Input/MouseClickEvent.hpp>
#include <Events/Input/MouseMoveEvent.hpp>

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

#endif // ITUENGINE_TESTEVENTSUBSCRIBTION_H