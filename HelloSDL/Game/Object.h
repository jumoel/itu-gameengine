#ifndef ITUENGINE_OBJECT_H
#define ITUENGINE_OBJECT_H

#include "GfxModel.h"
//#include "sdl_opengl.h"
#include "GL/glew.h"

class Object
{
public:
	std::string Name;

	Matrix4x4f *transformation;
	GfxModel *gfx;

	std::list<Object> *children;

	Object();
	~Object();

};

#endif