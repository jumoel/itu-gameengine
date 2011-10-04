#include "Camera.h"
#include "..\Managers\InputManager.h"
#include "..\Math\Matrix4x4f.h"
#include <cmath>

/* Region Construction & Deconstruction */

Camera::Camera()
{
	isLeftButtonDown = false;
	isRightButtonDown = false;

	InputManager::RegisterKeyboardEventHandler(this);
	InputManager::RegisterMouseClickEventHandler(this);
	InputManager::RegisterMouseMoveEventHandler(this);

	// TODO Enforce these Rules:
	/* |Position - LookAt| = 1 */
	/* |Up| = 1 */
	/* Look vector dotProduct Up = 0  */
}

Camera::~Camera()
{
}

/* Endregion Construction & Deconstruction */

//------------------------------------------------------------------------------------------------------------//

/* Region Camera Controls */

// Moves the position of the camera to the new location.
/* Implemented as moving the camera, up/down in a 2D plane, othogonally to the z axis, of the LookAt vector */
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
	float xUp = Up.x();
	float yUp = Up.y();
	float zUp = Up.z();

	float rUpPlusTx = xUp;
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
	float xLook = LookAt.x();
	float yLook = LookAt.y();
	float zLook = LookAt.z();
	float xUp = Up.x();
	float yUp = Up.y();
	float zUp = Up.z();
	

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
	float dotProduct = 0;

	float xLook = LookAt.x() - Position.x();
	float yLook = LookAt.y() - Position.y();
	float zLook = LookAt.z() - Position.z();

	dotProduct = Up.x()*xLook + Up.y()*yLook + Up.z()*zLook;
	
	if(dotProduct != 0.0f)
	{
		return;
	}

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

/* Endregion Camera Controls */

//------------------------------------------------------------------------------------------------------------//

/* Region Event handling */

//**************************************************************************************************//

/* Region Mouse Event handling */

void Camera::OnButtonDown(MouseClickEvent *button)
{
	auto buttonInput = button->GetInput();

	switch(buttonInput->button)
	{
		//Left + Right click
		case 1:
			isLeftButtonDown = true;
			break;
		case 3:
			isRightButtonDown = true;
			break;

		//Zoom control on scrollwheel
		case 4:
			ZoomCamera(0.5f);
			break;
		case 5:
			ZoomCamera(-0.5f);
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
		case 3:
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
		PitchCamera(motionInput->yrel * 0.01f);
		YawCamera(-motionInput->xrel * 0.01f);
	}
	else if(isRightButtonDown)
	{
		// TESTING FACILITIES !
		// REMOVE OR REDO WHEN TESTING IS DONE!
		lookx = this->LookAt.x();
		lookz = this->LookAt.z();
		
		auto asinLookx = asin(lookx);
		auto asinLookz = asin(lookz);

		this->LookAt.SetX( sinf( asinLookx + (motionInput->xrel * 0.1f)));
		this->LookAt.SetZ( sinf( asinLookz + (motionInput->xrel * 0.1f)));

		/*looky = this->LookAt.y();
		this->LookAt.SetY(looky + (motionInput->yrel * 0.01f));
		*/
		
		

		/*upz = this->Up.z();
		this->Up.SetZ(upz + (motionInput->yrel * 0.01f));*/
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
		//Control position Up/Down
		case SDLK_w:
			MoveCameraUpDown2D(0.5f);
			break;
		case SDLK_s:
			MoveCameraUpDown2D(-0.5f);
			break;

		//Control position Left/Right
		case SDLK_d:
			MoveCameraLeftRight2D(0.5f);
			break;
		case SDLK_a:
			MoveCameraLeftRight2D(-0.5f);
			break;

		//Control rotation
		case SDLK_q:
			RollCamera(0.5f);
			break;
		case SDLK_e:
			RollCamera(-0.5f);
			break;	

		//Reset the camera
		case SDLK_SPACE:
			ResetCamera();
			break;
	}
}

void Camera::OnKeyUp(KeyPressedEvent *key)
{

}

/* Endregion Keyboard Event handling */

//**************************************************************************************************//

/* Endregion Event handling */

//------------------------------------------------------------------------------------------------------------//