#ifndef ITUENGINE_CAMERA_H
#define ITUENGINE_CAMERA_H

#include "../Math/Vector3f.h"

class Camera
{
public:
	Camera();
	~Camera();

	Vector3f Up;
	Vector3f Position;
	Vector3f LookAt;
};

#endif