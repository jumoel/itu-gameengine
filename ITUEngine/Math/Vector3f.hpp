#ifndef ITUENGINE_VECTOR3F_H
#define ITUENGINE_VECTOR3F_H

#include <Abstractions/DataTypes.hpp>

class Vector3f
{
public:
	Vector3f(s32f x = 0.0f, s32f y = 0.0f, s32f z = 0.0f);
	~Vector3f();

	s32f x();
	s32f y();
	s32f z();

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

private:
	s32f vertices[3];
};

#endif