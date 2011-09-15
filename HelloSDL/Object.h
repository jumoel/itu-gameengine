#ifndef ITUENGINE_OBJECT_H
#define ITUENGINE_OBJECT_H

#include <list>
#include <vector>

#include "Math/Matrix4x4f.h"
#include "Math/Vector3f.h"

typedef std::list<Vertex3f> ColorList;
typedef std::list<Vertex3f> VertexList;
typedef std::list<Object> ObjectList;

class Object
{
public:
	Matrix4x4f *transformation;
	
	VertexList *vertices;
	ColorList *colors;

	ObjectList *children;

	Object();
	~Object();

protected:

private:

};

#endif