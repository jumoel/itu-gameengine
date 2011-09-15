#ifndef ITUENGINE_VECTOR3F_H
#define ITUENGINE_VECTOR3F_H

class Vector3f
{
public:
	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Vector3f();

	float x();
	float y();
	float z();

private:
	float vertices[3];
};

#endif