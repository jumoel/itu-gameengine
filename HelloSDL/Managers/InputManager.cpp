#include "InputManager.h"

InputManager::InputManager(void)
{
}


InputManager::~InputManager(void)
{
}


/* KEYBOARD EVENTS */
// Notifiers
void InputManager::NotifyKeyDown(KeyPressedEvent *key)
{
	m_KeyboardEventManager.Raise(IKeyboardEvent::KeyDown(key));
}

void InputManager::NotifyKeyUp(KeyPressedEvent *key)
{
	m_KeyboardEventManager.Raise(IKeyboardEvent::KeyUp(key));
}

// Register / Unregister event handlers
void InputManager::RegisterKeyboardEventHandler(IKeyboardEvent *client)
{
	m_KeyboardEventManager.Register(client);
}

void InputManager::UnregisterKeyboardEventHandler(IKeyboardEvent *client)
{
	m_KeyboardEventManager.Unregister(client);
}

/* MOUSE CLICK EVENTS */
// Notifiers
void InputManager::NotifyButtonDown(MouseClickEvent *button) 
{
	m_MouseClickEventManager.Raise(IMouseClickEvent::ButtonDown(button));
}

void InputManager::NotifyButtonUp(MouseClickEvent *button)
{
	m_MouseClickEventManager.Raise(IMouseClickEvent::ButtonUp(button));
}

// Register / Unregister event handlers
void InputManager::RegisterMouseClickEventHandler(IMouseClickEvent *client)
{
	m_MouseClickEventManager.Register(client);
}

void InputManager::UnregisterMouseClickEventHandler(IMouseClickEvent *client)
{
	m_MouseClickEventManager.Unregister(client);
}


/* MOUSE MOVE EVENTS */
// Notifiers
void InputManager::NotifyMotion(MouseMoveEvent *motion)
{
	m_MouseMoveEventManager.Raise(IMouseMoveEvent::Motion(motion));
}


// Register / Unregister event handlers
void InputManager::RegisterMouseMoveEventHandler(IMouseMoveEvent *client)
{
	m_MouseMoveEventManager.Register(client);
}

void InputManager::UnregisterMouseMoveEventHandler(IMouseMoveEvent *client)
{
	m_MouseMoveEventManager.Unregister(client);
}
