#include <Math/Vector2f.hpp>


Vector2f::Vector2f(float x, float y)
{
	this->vertices[0] = x;
	this->vertices[1] = y;
}

Vector2f::~Vector2f()
{
}

float Vector2f::x()
{
	return this->vertices[0];
}

float Vector2f::y()
{
	return this->vertices[1];
}



void Vector2f::SetX(float x)
{
	this->vertices[0] = x;
}

void Vector2f::SetY(float y)
{
	this->vertices[1] = y;
}

