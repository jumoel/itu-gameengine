#ifndef ITUENGINE_GFX_MODEL_H
#define ITUENGINE_GFX_MODEL_H

#include <list>
#include <vector>


#include "Material.h"
#include "../Math/Matrix4x4f.h"
#include "../Math/Vector3f.h"
//#include "sdl_opengl.h"
#include "GL/glew.h"



class GfxModel
{
public:
	GLuint vboId;
	GLuint cboId;
	GLuint tboId;

	Material *material;
	std::list<Vector3f> *vertices;


	GfxModel();
	~GfxModel();

	void CreateVBO();
	
};

#endif