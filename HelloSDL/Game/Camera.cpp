#include "Camera.h"
#include "..\Managers\InputManager.h"

Camera::Camera()
{
	isLeftButtonDown = false;
	isRightButtonDown = false;

	InputManager::RegisterKeyboardEventHandler(this);
	InputManager::RegisterMouseClickEventHandler(this);
	InputManager::RegisterMouseMoveEventHandler(this);
}

Camera::~Camera()
{
}

void Camera::OnButtonDown(MouseClickEvent *button)
{
	auto buttonInput = button->GetInput();

	float posz = 0;

	switch(buttonInput->button)
	{
		//Left + Right click
		case 1:
			isLeftButtonDown = true;
			break;
		case 2:
			isRightButtonDown = true;
			break;

		//Zoom control on scrollwheel
		case 4:
			posz = this->Position.z();
			this->Position.SetZ(posz - 0.5f);
			break;
		case 5:
			posz = this->Position.z();
			this->Position.SetZ(posz + 0.5f);
			break;
	}
}

void Camera::OnButtonUp(MouseClickEvent *button)
{
	auto buttonInput = button->GetInput();

	switch(buttonInput->button)
	{
		//Left + Right click
		case 1:
			isLeftButtonDown = false;
			break;
		case 2:
			isRightButtonDown = false;
			break;
	}
}

void Camera::OnMotion(MouseMoveEvent *motion)
{
	auto motionInput = motion->GetInput();

	float lookx = 0;
	float looky = 0;
	float lookz = 0;

	float upx = 0;
	float upy = 0;
	float upz = 0;

	if(isLeftButtonDown)
	{
		lookx = this->LookAt.x();
		this->LookAt.SetX(lookx + (motionInput->xrel * 0.01f));

		looky = this->LookAt.y();
		this->LookAt.SetY(looky + (motionInput->yrel * 0.01f));
	}
	else if(isRightButtonDown)
	{

	}
}

void Camera::OnKeyDown(KeyPressedEvent *key)
{
	auto keyInput = key->GetInput();
	
	float posx = 0;
	float posy = 0;

	float lookx = 0;
	float looky = 0;

	float upx = 0;

	switch(keyInput->keysym.sym)
	{
		//Control position x
		case SDLK_d:
			posx = this->Position.x();
			lookx = this->LookAt.x();
			this->Position.SetX(posx + 0.5f);
			this->LookAt.SetX(lookx + 0.5f);
			break;
		case SDLK_a:
			posx = this->Position.x();
			lookx = this->LookAt.x();
			this->Position.SetX(posx - 0.5f);
			this->LookAt.SetX(lookx - 0.5f);
			break;

		//Control position y
		case SDLK_w:
			posy = this->Position.y();
			looky = this->LookAt.y();
			this->Position.SetY(posy + 0.5f);
			this->LookAt.SetY(looky + 0.5f);
			break;
		case SDLK_s:
			posy = this->Position.y();
			looky = this->LookAt.y();
			this->Position.SetY(posy - 0.5f);
			this->LookAt.SetY(looky - 0.5f);
			break;

		//Control rotation
		case SDLK_q:
			upx = this->Up.x();
			this->Up.SetX(upx - 0.5f);
			break;
		case SDLK_e:
			upx = this->Up.x();
			this->Up.SetX(upx + 0.5f);
			break;		
	}
}

void Camera::OnKeyUp(KeyPressedEvent *key)
{

}