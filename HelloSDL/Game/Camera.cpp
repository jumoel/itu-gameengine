#include "Camera.h"
#include "..\Managers\InputManager.h"

Camera::Camera()
{
	InputManager::RegisterKeyboardEventHandler(this);
	InputManager::RegisterMouseClickEventHandler(this);
	InputManager::RegisterMouseMoveEventHandler(this);
}
Camera::~Camera()
{
}

void Camera::OnMotion(MouseMoveEvent *motion)
{

}

void Camera::OnButtonDown(MouseClickEvent *button)
{
	auto buttonInput = button->GetInput();

	switch(buttonInput->button)
	{
		//Control position x
		case 1:
			break;
		case 2:
			break;

		//Control position y
		case 3:
			break;
		case 4:
			break;

		//Control rotation
		case 5:
			break;
		case 6:
			break;		
	}
}

void Camera::OnButtonUp(MouseClickEvent *button)
{

}

void Camera::OnKeyDown(KeyPressedEvent *key)
{
	auto keyInput = key->GetInput();

	switch(keyInput->keysym.sym)
	{
		//Control position x
		case SDLK_d:
			break;
		case SDLK_a:
			break;

		//Control position y
		case SDLK_w:
			break;
		case SDLK_s:
			break;

		//Control rotation
		case SDLK_q:
			break;
		case SDLK_e:
			break;		
	}
}

void Camera::OnKeyUp(KeyPressedEvent *key)
{

}