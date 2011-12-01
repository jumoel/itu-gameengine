#ifndef ITUENGINE_VECTOR2F_H
#define ITUENGINE_VECTOR2F_H

#include <Abstractions/DataTypes.hpp>

class Vector2f
{
public:
	Vector2f(s32f x = 0.0f, s32f y = 0.0f);
	~Vector2f();

	s32f x();
	s32f y();

	void SetX(float x);
	void SetY(float y);

private:
	s32f vertices[2];
};



#endif
