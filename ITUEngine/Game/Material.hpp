#ifndef ITUENGINE_Material_H
#define ITUENGINE_Material_H


#include <list>
#include <vector>

#include <iostream>
#include <Math/Vector3f.hpp>
#include <Game/Texture.hpp>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure

class Material
{
public:
	Texture *texture;

	float *spec;
	float shine;

	float shininess;
	float *diffuse;
	float *specular;
	float *emissive;
	float *ambient;

	aiShadingMode shader;

	std::list<Vector3f> *colors;
	std::list<TexCoord> *uv;

	Material();
	~Material();
};

#endif

