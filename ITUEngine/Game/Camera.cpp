#include <Game/Camera.hpp>
#include <Managers\InputManager.hpp>
#include <Math\Matrix4x4f.hpp>
#include <cmath>
#include <SDL.h>
#include <Managers/EventManager.hpp>
#include <Events/EventData/EventData.hpp>
#include <Events/Interfaces/IEventData.hpp>
#include <SDL_events.h>
#include <memory>

/* Region Construction & Deconstruction */

Camera::Camera()
{
	isLeftButtonDown = false;
	isRightButtonDown = false;

	InputManager::RegisterKeyboardEventHandler(this);
	InputManager::RegisterMouseMoveEventHandler(this);

	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;

	grab_on = true;
	SDL_WM_GrabInput(SDL_GRAB_ON);
}

Camera::~Camera()
{
}

/* Endregion Construction & Deconstruction */

//------------------------------------------------------------------------------------------------------------//

/* Region Camera Controls */

// Moves the position of the camera to the new location.
/* Implemented as moving the camera, up/down in a 2D plane, orthogonally to the z axis, of the LookAt vector */
void Camera::MoveCamera3D(Vector3f *newPosition)
{
	float xDirection = newPosition->x() - Position.x();
	float yDirection = newPosition->y() - Position.y();
	float zDirection = newPosition->z() - Position.z();

	Position.SetX(newPosition->x());
	Position.SetY(newPosition->y());
	Position.SetZ(newPosition->z());
	
	LookAt.SetX(xDirection + LookAt.x());
	LookAt.SetY(yDirection + LookAt.y());
	LookAt.SetZ(zDirection + LookAt.z());
}

//Rotates the camera around the x axis of the LookAt vector. Positive is clockwise, negative is counter-clockwise.
//Limited to 90° Up/Down
void Camera::PitchCamera(float radians)
{
	float yUp = Up.y();
	float zUp = Up.z();

	float rUpPlusTy = yUp*cos(radians) - zUp*sin(radians);
	float rUpPlusTz = yUp*sin(radians) + zUp*cos(radians);

	if(rUpPlusTy <= 0)
	{
		return;
	}

	Up.SetY(rUpPlusTy);
	Up.SetZ(rUpPlusTz);

	float xPosition = Position.x();
	float yPosition = Position.y();
	float zPosition = Position.z();

	float xLookDirection = LookAt.x() - Position.x();
	float yLookDirection = LookAt.y() - Position.y();
	float zLookDirection = LookAt.z() - Position.z();

	float rLookPlusTx =	xLookDirection + xPosition;
	float rLookPlusTy = yLookDirection*cos(radians) - zLookDirection*sin(radians) + yPosition;
	float rLookPlusTz = yLookDirection*sin(radians) + zLookDirection*cos(radians) + zPosition;

	LookAt.SetX(rLookPlusTx);
	LookAt.SetY(rLookPlusTy);
	LookAt.SetZ(rLookPlusTz);
}

//Rotates the camera around the y axis, of Up vector. Positive is clockwise, negative is counter-clockwise.
void Camera::YawCamera(float radians)
{
	float xPosition = Position.x();
	float yPosition = Position.y();
	float zPosition = Position.z();

	float xLookDirection = LookAt.x() - Position.x();
	float yLookDirection = LookAt.y() - Position.y();
	float zLookDirection = LookAt.z() - Position.z();
	
	float rLookPlusTx = xLookDirection*cos(radians) - zLookDirection*sin(radians) + xPosition;
	float rLookPlusTy = yLookDirection + yPosition;
	float rLookPlusTz = xLookDirection*sin(radians) + zLookDirection*cos(radians) + zPosition;

	LookAt.SetX(rLookPlusTx);
	LookAt.SetY(rLookPlusTy);
	LookAt.SetZ(rLookPlusTz);
}

//Rotates the camera around the z axis, of the LookAt vector. Positive is clockwise, negative is counter-clockwise.
void Camera::RollCamera(float radians)
{
	float xUp = Up.x();
	float yUp = Up.y();

	float rUpPlusTx = xUp*cos(radians) - yUp*sin(radians);
	float rUpPlusTy = xUp*sin(radians) + yUp*cos(radians);

	if(rUpPlusTy <= 0)
	{
		return;
	}

	Up.SetX(rUpPlusTx);
	Up.SetY(rUpPlusTy);
}

//Zooms the camera in or out, Negative is out and Positive is in.
/* Implemented as moving the camera in/out in a line parallel to the z axis, of the LookAt vector */
void Camera::ZoomCamera(float distance)
{
	float xDirection = LookAt.x() - Position.x();
	float yDirection = LookAt.y() - Position.y();
	float zDirection = LookAt.z() - Position.z();

	xDirection *= distance;
	yDirection *= distance;
	zDirection *= distance;

	Position.SetX(xDirection + Position.x());
	Position.SetY(yDirection + Position.y());
	Position.SetZ(zDirection + Position.z());

	LookAt.SetX(xDirection + LookAt.x());
	LookAt.SetY(yDirection + LookAt.y());
	LookAt.SetZ(zDirection + LookAt.z());
}

// Moves the camera in a direction.
/* Implemented as moving the camera, up/down in a 2D plane, othogonally to the z axis, of the LookAt vector */
void Camera::MoveCameraUpDown2D(float distance)
{
	float xDirection = Up.x();
	float yDirection = Up.y();
	float zDirection = Up.z();

	xDirection *= distance;
	yDirection *= distance;
	zDirection *= distance;

	Position.SetX(xDirection + Position.x());
	Position.SetY(yDirection + Position.y());
	Position.SetZ(zDirection + Position.z());

	LookAt.SetX(xDirection + LookAt.x());
	LookAt.SetY(yDirection + LookAt.y());
	LookAt.SetZ(zDirection + LookAt.z());
}

void Camera::MoveCameraLeftRight2D(float distance)
{
	float xLook = LookAt.x() - Position.x();
	float yLook = LookAt.y() - Position.y();
	float zLook = LookAt.z() - Position.z();

	//Create the Cross Product vector, Perpendicular to the Up/LookAt plane
	float xDirection = Up.y() * zLook - Up.z() * yLook;
	float yDirection = Up.z() * xLook - Up.x() * zLook;
	float zDirection = Up.x() * yLook - Up.y() * xLook;

	xDirection *= distance;
	yDirection *= distance;
	zDirection *= distance;

	Position.SetX(xDirection + Position.x());
	Position.SetY(yDirection + Position.y());
	Position.SetZ(zDirection + Position.z());

	LookAt.SetX(xDirection + LookAt.x());
	LookAt.SetY(yDirection + LookAt.y());
	LookAt.SetZ(zDirection + LookAt.z());
}

void Camera::ResetCamera()
{
	Position.SetX(0);
	Position.SetY(0);
	Position.SetZ(0);

	LookAt.SetX(0);
	LookAt.SetY(0);
	LookAt.SetZ(-1);

	Up.SetX(0);
	Up.SetY(1);
	Up.SetZ(0);
}


void Camera::Update(unsigned int deltaT)
{
	float real_speed = (float)deltaT / 1000.0f * (float)speed;

	if (moveUp)
	{
		MoveCameraUpDown2D(-real_speed * updownfactor);
	}

	if (moveDown)
	{
		MoveCameraUpDown2D(real_speed * updownfactor);
	}

	if (moveLeft)
	{
		MoveCameraLeftRight2D(real_speed);
	}

	if (moveRight)
	{
		MoveCameraLeftRight2D(-real_speed);
	}
}

/* Endregion Camera Controls */

//------------------------------------------------------------------------------------------------------------//

/* Region Event handling */

//**************************************************************************************************//

/* Region Mouse Event handling */

void Camera::OnMotion(MouseMoveEvent *motion)
{
	auto motionInput = motion->GetInput();
	auto screenInfo = SDL_GetVideoInfo();
	auto screenWidth = screenInfo->current_w;
	auto screenHeight = screenInfo->current_h;

	// std::cout << "Screenwidth: " << screenWidth << ", X: " << motionInput->x << std::endl; 

	if (motionInput->x > (screenWidth - gutter_px) && motionInput->x < (screenWidth + gutter_px))
	{
		moveRight = true;
		moveLeft = false;
	}
	else if (motionInput->x < gutter_px && motionInput->x > -gutter_px)
	{
		moveRight = false;
		moveLeft = true;
	}
	else
	{
		moveRight = false;
		moveLeft = false;
	}

	if (motionInput->y > (screenHeight - gutter_px) && motionInput->y < (screenHeight + gutter_px))
	{
		moveUp = true;
		moveDown = false;
	}
	else if (motionInput->y < gutter_px && motionInput->y > -gutter_px)
	{
		moveUp = false;
		moveDown = true;
	}
	else
	{
		moveUp = false;
		moveDown = false;
	}
}

/* Endregion Mouse Event handling */

//**************************************************************************************************//

/* Region Keyboard Event handling */

void Camera::OnKeyDown(KeyPressedEvent *key)
{
	auto keyInput = key->GetInput();

	switch(keyInput->keysym.sym)
	{
	case SDLK_w:
		grab_on = !grab_on;

		if (grab_on)
		{
			SDL_WM_GrabInput(SDL_GRAB_ON);
		}
		else
		{
			SDL_WM_GrabInput(SDL_GRAB_OFF);
		}
		break;
	}
}

void Camera::OnKeyUp(KeyPressedEvent *key)
{
	//Ignore key up events
}

/* Endregion Keyboard Event handling */

//**************************************************************************************************//

/* Endregion Event handling */

//------------------------------------------------------------------------------------------------------------//