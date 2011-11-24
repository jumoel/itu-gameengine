#ifndef ITUENGINE_OBJECT_H
#define ITUENGINE_OBJECT_H

#include <Game/GfxModel.hpp>
#include <Game/Model.hpp>

class Object
{
public:
	std::string Name;

	Matrix4x4f *transformation;
	GfxModel *gfx;
	Model *model;

	std::list<Object> *children;

	int VboId;
	int VboOffset;

	Object();
	~Object();

};

#endif