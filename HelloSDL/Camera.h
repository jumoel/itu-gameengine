#ifndef ITUENGINE_CAMERA_H
#define ITUENGINE_CAMERA_H

#include "Object.h"
#include "Math/Vector3f.h"

class Camera : public Object
{
public:
	Vector3f *Up;
	Vector3f *Position;
	Vector3f *LookAt;

	virtual bool IsCamera() const;
};

#endif