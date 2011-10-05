#include "GfxModel.h"
#include <iostream>
#include "../Managers/MediaManager.h"

GfxModel::GfxModel()
{
	this->colors = new std::list<Vector3f>();
	this->vertices = new std::list<Vector3f>();
	this->uv = new std::list<TexCoord>();
	this->texture = NULL;
	this->spec = new float[4];
	for(int i = 0; i < 4; i++)
	{
		spec[i] = 0.0f;
	}
	this->shine = 0.0f;
}

GfxModel::~GfxModel()
{
	delete this->colors;
	delete this->vertices;
	delete this->uv;
	delete [] this->spec;
}


void GfxModel::CreateVBO()
{
	GLfloat *verts = new GLfloat[vertices->size()*3];
	GLfloat *color = new GLfloat[colors->size()*3];
	GLfloat *uvs = new GLfloat[uv->size()*2];

	auto vertex_iter = vertices->begin();
	auto color_iter = colors->begin();
	auto uv_iter = uv->begin();

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

	i = 0;

	while (uv_iter != uv->end())
	{
		uvs[i] = uv_iter->u;
		uvs[i+1] = uv_iter->v;

		uv_iter++;
		i += 2;
	}

	glGenBuffersARB(1, &vboId);																				//Generate VBO and get associated ID
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);															//Bind the VBO in order to use it
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size()*3*sizeof(float), verts, GL_STATIC_DRAW_ARB);		//Upload data to the VBO


	glGenBuffersARB(1, &cboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, cboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, colors->size()*3*sizeof(float), color, GL_STATIC_DRAW_ARB);

	if(texture != NULL)
	{
		// Generate And Bind The Texture Coordinate Buffer
		glGenBuffersARB( 1, &tboId );							// Get A Valid Name
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, tboId);			// Bind The Buffer

		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, vertices->size()*2*sizeof(float), uvs, GL_STATIC_DRAW_ARB );
	}


	delete [] verts;
	delete [] color;
}