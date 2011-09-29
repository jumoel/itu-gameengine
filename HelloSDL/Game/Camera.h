#ifndef ITUENGINE_CAMERA_H
#define ITUENGINE_CAMERA_H

#include "../Math/Vector3f.h"
#include "../Events/Input/KeyPressedEvent.h"
#include "../Events/Input/MouseMoveEvent.h"
#include "../Events/Input/MouseClickEvent.h"

class Camera : public IKeyboardEvent, public IMouseClickEvent, public IMouseMoveEvent
{
public:
	Camera();
	~Camera();

	Vector3f Up;
	Vector3f Position;
	Vector3f LookAt;

protected:
	void OnMotion(MouseMoveEvent *motion);
	void OnButtonDown(MouseClickEvent *button);
	void OnButtonUp(MouseClickEvent *button);
	void OnKeyDown(KeyPressedEvent *key);
	void OnKeyUp(KeyPressedEvent *key);

private:
	bool isLeftButtonDown;
	bool isRightButtonDown;
};

#endif