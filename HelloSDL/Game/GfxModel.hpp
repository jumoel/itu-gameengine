#ifndef ITUENGINE_GFX_MODEL_H
#define ITUENGINE_GFX_MODEL_H

#include <list>
#include <vector>

#include <Game/Texture.hpp>
#include <Math/Matrix4x4f.hpp>
#include <Math/Vector3f.hpp>

class TexCoord                                 // Texture Coordinate Class
{
public:
    float u;									// U Component
    float v;									// V Component

	TexCoord(){}
	TexCoord(float uIn, float vIn){ u = uIn; v = vIn; }
	~TexCoord(){}
};

class GfxModel
{
public:
	GLuint vboId;
	GLuint cboId;
	GLuint tboId;

	Texture *texture;

	std::list<Vector3f> *vertices;
	std::list<Vector3f> *colors;
	std::list<TexCoord> *uv;


	GfxModel();
	~GfxModel();

	//void CreateModel(std::list<Vector3f> *verticesIn, std::list<Vector3f> *colorsIn = NULL, TexCoord *uvIn = NULL);
	void CreateVBO();
	
};

#endif