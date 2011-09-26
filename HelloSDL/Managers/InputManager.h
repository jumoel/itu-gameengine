#ifndef ITUENGINE_INPUTMANAGER_H
#define ITUENGINE_INPUTMANAGER_H

#include "EventManager.h"
#include "..\Events\Input\KeyPressedEvent.h"
#include "..\Events\Input\MouseClickEvent.h"
#include "..\Events\Input\MouseMoveEvent.h"

//TODO: Make this class into something static, either with Namespace + globals or something smarter.
// DET BURDE VÆRE MULIGT AT LAVE EVENTMANAGERS static, og så lave NAMESPACE Functions her... Det virker smartest

class InputManager
{
protected: 
	EventManager<IKeyboardEvent> m_KeyboardEventManager; //instantiate the general event manager for keyboard events
	EventManager<IMouseClickEvent> m_MouseClickEventManager; //instantiate the general event manager for mouse click events
	EventManager<IMouseMoveEvent> m_MouseMoveEventManager; //instantiate the general event manager for mouse move events
public:
	InputManager(void);
	~InputManager(void);

	/* KEYBOARD EVENTS */
	// Notifiers
	void NotifyKeyDown(KeyPressedEvent *key);
	void NotifyKeyUp(KeyPressedEvent *key);

	// Register / Unregister event handlers
	void RegisterKeyboardEventHandler(IKeyboardEvent *client);
	void UnregisterKeyboardEventHandler(IKeyboardEvent *client);

	/* MOUSE CLICK EVENTS */
	// Notifiers
	void NotifyButtonDown(MouseClickEvent *button);
	void NotifyButtonUp(MouseClickEvent *button);

	// Register / Unregister event handlers
	void RegisterMouseClickEventHandler(IMouseClickEvent *client);
	void UnregisterMouseClickEventHandler(IMouseClickEvent *client);

	/* MOUSE MOVE EVENTS */
	// Notifiers
	void NotifyMotion(MouseMoveEvent *motion);

	// Register / Unregister event handlers
	void RegisterMouseMoveEventHandler(IMouseMoveEvent *client);
	void UnregisterMouseMoveEventHandler(IMouseMoveEvent *client);
};

#endif