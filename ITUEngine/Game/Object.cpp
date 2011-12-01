#include <Game/Object.hpp>
#include <iostream>

Object::Object()
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->gfx = new GfxModel();
	this->model = new Model();
	this->physicsModel = NULL;
}

Object::Object(PhysicsModel *physics)
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->gfx = new GfxModel();
	this->model = new Model();
	this->physicsModel = physics;
}

Object::~Object()
{
	delete this->transformation;
	delete this->gfx;
	delete this->model;
	delete this->physicsModel;
	auto child_iter = children->begin();
	while(child_iter != children->end())
	{
		delete &(*child_iter);
	}
	delete this->children;
}
