#ifndef ITUENGINE_MATRIX4X4F_H
#define ITUENGINE_MATRIX4X4F_H
#include <Math/Vector3f.hpp>

#define PI 3.1415926f

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

	Matrix4x4f* createScale(float x, float y, float z);
	Matrix4x4f* createTranslate(float x, float y, float z);
	Matrix4x4f* createRotate(float degrees, float x, float y, float z);

	static Matrix4x4f Multiply(Matrix4x4f a, Matrix4x4f b);

	void Print();
protected:


private:


};

#endif