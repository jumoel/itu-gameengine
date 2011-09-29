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

void Camera::OnMotion(MouseMoveEvent *motion)
{
	
}

void Camera::OnButtonDown(MouseClickEvent *button)
{
	auto buttonInput = button->GetInput();

	float posx = 0;
	float posy = 0;
	float posz = 0;

	float lookx = 0;
	float looky = 0;
	float lookz = 0;

	float upx = 0;
	float upy = 0;
	float upz = 0;


	switch(buttonInput->button)
	{
		//Left + Right click
		case 1:
			break;
		case 2:
			break;

		//Zoom control on scrollwheel
		case 4:
			posz = this->Position.z();
			this->Position.SetZ(--posz);
			break;
		case 5:
			posz = this->Position.z();
			this->Position.SetZ(++posz);
			break;
	}
}

void Camera::OnButtonUp(MouseClickEvent *button)
{

}

void Camera::OnKeyDown(KeyPressedEvent *key)
{
	auto keyInput = key->GetInput();
	
	float posx = 0;
	float posy = 0;
	float posz = 0;

	float lookx = 0;
	float looky = 0;
	float lookz = 0;

	float upx = 0;
	float upy = 0;
	float upz = 0;

	switch(keyInput->keysym.sym)
	{
		//Control position x
		case SDLK_d:
			posx = this->Position.x();
			lookx = this->LookAt.x();
			this->Position.SetX(++posx);
			this->LookAt.SetX(++lookx);
			break;
		case SDLK_a:
			posx = this->Position.x();
			lookx = this->LookAt.x();
			this->Position.SetX(--posx);
			this->LookAt.SetX(--lookx);
			break;

		//Control position y
		case SDLK_w:
			posy = this->Position.y();
			looky = this->LookAt.y();
			this->Position.SetY(++posy);
			this->LookAt.SetY(++looky);
			break;
		case SDLK_s:
			posy = this->Position.y();
			looky = this->LookAt.y();
			this->Position.SetY(--posy);
			this->LookAt.SetY(--looky);
			break;

		//Control rotation
		case SDLK_q:
			upx = this->Up.x();
			this->Up.SetX(upx - 0.1f);
			break;
		case SDLK_e:
			upx = this->Up.x();
			this->Up.SetX(upx + 0.1f);
			break;		
	}
}

void Camera::OnKeyUp(KeyPressedEvent *key)
{

}