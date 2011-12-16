#ifndef ITUENGINE_OBJECT_H
#define ITUENGINE_OBJECT_H

#include <Game/GfxModel.hpp>
#include <Game/Model.hpp>
#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>

class Object
{
public:
	std::string Name;

	Matrix4x4f *transformation;
	GfxModel *gfx;
	Model *model;
	PhysicsModel *physicsModel;

	std::list<Object> *children;

	int VboId;
	int VboOffset;

	void SetPos2D(float x, float y);
	Vector3f* getPos();
	void Rotate(float degrees, float x, float y, float z);
	void setLookAt2D(float x, float y);
	void SetScale(float x, float y, float z);
	void SetForward(float x, float y);

	Object();
	Object(PhysicsModel *physics);
	~Object();
private:
	Vector3f *pos;
	Vector2f *forward2D;
	Matrix4x4f *rotation;
	Matrix4x4f *scale;

};

#endif