#ifndef ITUENGINE_MATRIX4X4F_H
#define ITUENGINE_MATRIX4X4F_H
#include <Math/Vector3f.hpp>

class Matrix4x4f
{
public:
	float data[16];

	Matrix4x4f();

	~Matrix4x4f();

	void Reset();
	Matrix4x4f* Scale(float x, float y, float z);
	Matrix4x4f* Translate(float x, float y, float z);
	Matrix4x4f* Rotate(float degrees, float x, float y, float z);
	Matrix4x4f* MultiplyWith(Matrix4x4f other);
	Vector3f MultiplyWithVector(Vector3f inVector);

	static Matrix4x4f Multiply(Matrix4x4f a, Matrix4x4f b);
protected:


private:


};

#endif