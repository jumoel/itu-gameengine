#ifndef ITUENGINE_OBJECT_H
#define ITUENGINE_OBJECT_H

#include <list>
#include <vector>

#include "../Math/Matrix4x4f.h"
#include "../Math/Vector3f.h"

class Object
{
public:
	std::string Name;

	Matrix4x4f *transformation;
	
	std::list<Vector3f> *vertices;
	std::list<Vector3f> *colors;

	std::list<Object> *children;

	Object();
	~Object();
};

#endif