#ifndef ITUENGINE_Material_H
#define ITUENGINE_Material_H


#include <list>
#include <vector>

#include <iostream>
#include <Math/Vector3f.hpp>
#include <Game/Texture.hpp>

class Material
{
public:
	Texture *texture;

	float *spec;
	float shine;

	std::list<Vector3f> *colors;
	std::list<TexCoord> *uv;

	Material();
	~Material();
};

#endif

