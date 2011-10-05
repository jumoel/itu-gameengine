#include <Game/GfxModel.hpp>
#include <iostream>
#include <Managers/MediaManager.hpp>

GfxModel::GfxModel()
{
	this->vertices = new std::list<Vector3f>();
	this->material = new Material();
}

GfxModel::~GfxModel()
{
	
	delete this->vertices;
	
}


void GfxModel::CreateVBO()
{
	GLfloat *verts = new GLfloat[vertices->size()*3];
	GLfloat *color = new GLfloat[material->colors->size()*3];
	GLfloat *uvs = new GLfloat[material->uv->size()*2];

	auto vertex_iter = vertices->begin();
	auto color_iter = material->colors->begin();
	auto uv_iter = material->uv->begin();

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

	while (color_iter != material->colors->end())
	{
		color[i] = color_iter->x();
		color[i+1] = color_iter->y();
		color[i+2] = color_iter->z();

		color_iter++;
		i += 3;
	}

	i = 0;

	while (uv_iter != material->uv->end())
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
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, material->colors->size()*3*sizeof(float), color, GL_STATIC_DRAW_ARB);

	if(material->texture != NULL)
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
