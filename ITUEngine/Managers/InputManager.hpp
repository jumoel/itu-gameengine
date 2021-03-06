#ifndef ITUENGINE_INPUTMANAGER_H
#define ITUENGINE_INPUTMANAGER_H

#include <Events/Interfaces/InterfaceTemplateEventManager.hpp>
#include <Events/Input/KeyPressedEvent.hpp>
#include <Events/Input/MouseClickEvent.hpp>
#include <Events/Input/MouseMoveEvent.hpp>

namespace InputManager
{ 
	static InterfaceTemplateEventManager<IKeyboardEvent> KeyboardEventManager; //instantiate the general event manager for keyboard events
	static InterfaceTemplateEventManager<IMouseClickEvent> MouseClickEventManager; //instantiate the general event manager for mouse click events
	static InterfaceTemplateEventManager<IMouseMoveEvent> MouseMoveEventManager; //instantiate the general event manager for mouse move events

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