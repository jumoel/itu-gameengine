#include "InputManager.h"


/* KEYBOARD EVENTS */
// Notifiers
void InputManager::NotifyKeyDown(KeyPressedEvent *key)
{
	KeyboardEventManager.Raise(IKeyboardEvent::KeyDown(key));
}

void InputManager::NotifyKeyUp(KeyPressedEvent *key)
{
	KeyboardEventManager.Raise(IKeyboardEvent::KeyUp(key));
}

// Register / Unregister event handlers
void InputManager::RegisterKeyboardEventHandler(IKeyboardEvent *client)
{
	KeyboardEventManager.Register(client);
}

void InputManager::UnregisterKeyboardEventHandler(IKeyboardEvent *client)
{
	KeyboardEventManager.Unregister(client);
}

/* MOUSE CLICK EVENTS */
// Notifiers
void InputManager::NotifyButtonDown(MouseClickEvent *button) 
{
	MouseClickEventManager.Raise(IMouseClickEvent::ButtonDown(button));
}

void InputManager::NotifyButtonUp(MouseClickEvent *button)
{
	MouseClickEventManager.Raise(IMouseClickEvent::ButtonUp(button));
}

// Register / Unregister event handlers
void InputManager::RegisterMouseClickEventHandler(IMouseClickEvent *client)
{
	MouseClickEventManager.Register(client);
}

void InputManager::UnregisterMouseClickEventHandler(IMouseClickEvent *client)
{
	MouseClickEventManager.Unregister(client);
}


/* MOUSE MOVE EVENTS */
// Notifiers
void InputManager::NotifyMotion(MouseMoveEvent *motion)
{
	MouseMoveEventManager.Raise(IMouseMoveEvent::Motion(motion));
}


// Register / Unregister event handlers
void InputManager::RegisterMouseMoveEventHandler(IMouseMoveEvent *client)
{
	MouseMoveEventManager.Register(client);
}

void InputManager::UnregisterMouseMoveEventHandler(IMouseMoveEvent *client)
{
	MouseMoveEventManager.Unregister(client);
}
