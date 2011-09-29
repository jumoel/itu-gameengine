#include "Object.h"
#include <iostream>


Object::Object()
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->gfx = new GfxModel();
}

Object::~Object()
{
	delete this->transformation;
	auto child_iter = children->begin();
	while(child_iter != children->end())
	{
		delete &(*child_iter);
	}
	delete this->children;
}
