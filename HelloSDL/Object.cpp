#include "Object.h"

Object::Object()
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->colors = new std::list<Vector3f>();
	this->vertices = new std::list<Vector3f>();
}

Object::~Object()
{
}