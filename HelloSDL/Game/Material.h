#ifndef ITUENGINE_Material_H
#define ITUENGINE_Material_H


#include <list>
#include <vector>

#include <iostream>
#include "SDL.h"
#include "GL/glew.h"
#include "../Math/Vector3f.h"


#include "Texture.h"

class Material
{
public:
	Texture *texture;

	float *spec;
	int shine;

	std::list<Vector3f> *colors;
	std::list<TexCoord> *uv;

	Material();
	~Material();
};

#endif

