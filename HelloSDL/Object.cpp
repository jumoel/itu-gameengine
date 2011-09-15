#include "Object.h"

Object::Object()
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->colors = new colorlist();
	this->vertices = new vertexlist();
}

Object::~Object()
{
}