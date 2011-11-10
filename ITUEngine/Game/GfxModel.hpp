#ifndef ITUENGINE_GFX_MODEL_H
#define ITUENGINE_GFX_MODEL_H

#include <vector>

#include <Math/Matrix4x4f.hpp>
#include <Math/Vector3f.hpp>
#include <Game/Material.hpp>



class GfxModel
{
public:
	GLuint vboId;
	GLuint cboId;
	GLuint tboId;

	Material *material;
	std::vector<Vector3f> *vertices;

	GfxModel();
	~GfxModel();

	void CreateVBO();
	
};

#endif
