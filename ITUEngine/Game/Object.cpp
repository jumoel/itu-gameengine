#include <Game/Object.hpp>
#include <iostream>
#include <cmath>


Object::Object()
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->gfx = new GfxModel();
	this->model = new Model();
	this->physicsModel = NULL;
	pos = new Vector3f(0.0f, 0.0f, 0.0f);
	rotation = new Matrix4x4f();
	rotation->Reset();
	scale = new Matrix4x4f();
	scale->Reset();
	forward2D = new Vector2f(1.0f,0.0f);
}

Object::Object(PhysicsModel *physics)
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->gfx = new GfxModel();
	this->model = new Model();
	this->physicsModel = physics;
	pos = new Vector3f(0.0f, 0.0f, 0.0f);
	rotation = new Matrix4x4f();
	rotation->Reset();
	scale = new Matrix4x4f();
	scale->Reset();
	forward2D = new Vector2f(1.0f,0.0f);
}

Object::~Object()
{
	delete this->transformation;

	if(this->model != NULL)
	{
	//	delete this->model;
	}
	if(this->gfx)
	{
		delete this->gfx;
	}

	delete this->physicsModel;
	delete this->children;

	delete pos;
	delete rotation;
	delete scale;
}

void Object::SetPos2D(float x, float y)
{
	pos->SetX(x), pos->SetY(y);
	if(physicsModel != NULL) physicsModel->SetPosition(x,y);
	transformation->Reset();
	transformation->Translate(pos->x(), pos->y(), pos->z());
	transformation->MultiplyWith(*rotation);
	transformation->MultiplyWith(*scale);
}

void Object::Rotate(float degrees, float x, float y, float z)
{
	auto temp = (transformation->createRotate(degrees, x, y, z));
	rotation->MultiplyWith(*temp);
	delete temp;
	transformation->Reset();
	transformation->Translate(pos->x(), pos->y(), pos->z());
	transformation->MultiplyWith(*rotation);
	transformation->MultiplyWith(*scale);
}

void Object::SetScale(float x, float y, float z)
{
	scale = transformation->createScale(x,y,z);
	if(physicsModel != NULL) physicsModel->scale(x,y);
	transformation->Reset();
	transformation->Translate(pos->x(), pos->y(), pos->z());
	transformation->MultiplyWith(*rotation);
	transformation->MultiplyWith(*scale);

}

Vector3f* Object::getPos()
{
	return pos;
}

void Object::SetForward(float x, float y)
{
	forward2D->SetX(x);
	forward2D->SetY(y);
}

void Object::setLookAt2D(float x, float y)
{
	
	float length = sqrt(x*x + y*y);
	if(length > 0)
	{	
		physicsModel->SetDirection(x,y);

		if (rotation != nullptr)
		{
			delete rotation;
		}
		rotation = transformation->createRotate(90.0f, 1.0f, 0.0f, 0.0f);
		x = x/length;
		y = y/length;

		float degrees = atan2(y,x) - atan2(forward2D->y(),forward2D->x());
		//float degrees = atan2(forward2D->y(),forward2D->x()) - atan2(y,x);
		degrees = (degrees * 180)/PI;
		
		
		//std::cout << "Degrees: " << degrees << std::endl;
		
		
		auto temp = (transformation->createRotate(degrees, 0.0f, 1.0f, 0.0f));
		rotation->MultiplyWith(*temp);
		delete temp;
		transformation->Reset();
		transformation->Translate(pos->x(), pos->y(), pos->z());
		transformation->MultiplyWith(*rotation);
		transformation->MultiplyWith(*scale);
	}
	else
	{
		std::cout << "Error setting look at 2d, length = 0" << std::endl;
	}
}
