#include "Object.h"
#include <iostream>


Object::Object()
{
	this->transformation = new Matrix4x4f();
	this->children = new std::list<Object>();
	this->colors = new std::list<Vector3f>();
	this->vertices = new std::list<Vector3f>();
}

Object::~Object()
{
}

void Object::CreateVBO()
{
	GLfloat *verts = new GLfloat[vertices->size()*3];
	GLfloat *color = new GLfloat[colors->size()*3];

	auto vertex_iter = vertices->begin();
	auto color_iter = colors->begin();

	int i = 0;

	while (vertex_iter != vertices->end())
	{
		verts[i] = vertex_iter->x();
		verts[i+1] = vertex_iter->y();
		verts[i+2] = vertex_iter->z();

		vertex_iter++;
		i += 3;
	}

	i = 0;

	while (color_iter != colors->end())
	{
		color[i] = color_iter->x();
		color[i+1] = color_iter->y();
		color[i+2] = color_iter->z();

		color_iter++;
		i += 3;
	}

	glGenBuffersARB(1, &vboId);																				//Generate VBO and get associated ID
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);															//Bind the VBO in order to use it
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size()*3*sizeof(float), verts, GL_STATIC_DRAW_ARB);		//Upload data to the VBO


	glGenBuffersARB(1, &cboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, cboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, colors->size()*3*sizeof(float), color, GL_STATIC_DRAW_ARB);

	delete [] verts;
	delete [] color;
}