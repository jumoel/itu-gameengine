#include <Managers/SceneGraphManager.hpp>
#include <SDL.h>
//#include "sdl_opengl.h"
#include "GL/glew.h"
#include <iostream>

SceneGraphManager::SceneGraphManager(Camera *CameraObject, Object *RootNode) :
	CameraObject(CameraObject),
	RootNode(RootNode),
	LastTime(0),
	DeltaTime(0)
{
}
/*
void SceneGraphManager::Render(Uint32 CurrentTime, bool vboOn)
{	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		CameraObject->Position.x(), CameraObject->Position.y(), CameraObject->Position.z(), 
		CameraObject->LookAt.x(), CameraObject->LookAt.y(), CameraObject->LookAt.z(), 
		CameraObject->Up.x(), CameraObject->Up.y(), CameraObject->Up.z()
		);

	if(vboOn)
	{
		SceneGraphManager::RenderObjectVBO(this->RootNode);
	}
	else
	{
		SceneGraphManager::RenderObject(this->RootNode);
	}

	SDL_GL_SwapBuffers();

	LastTime = CurrentTime;
}


void SceneGraphManager::RenderObject(Object *obj)
{
	glPushMatrix();

	glMultMatrixf(obj->transformation->data);

	auto color_iter = obj->gfx->material->colors->begin();
	auto vertex_iter = obj->gfx->vertices->begin();

	glBegin(GL_TRIANGLES);

	while (color_iter != obj->gfx->material->colors->end() && vertex_iter != obj->gfx->vertices->end())
	{
		glColor3f(color_iter->x(), color_iter->y(), color_iter->z());
		glVertex3f(vertex_iter->x(), vertex_iter->y(), vertex_iter->z());

		color_iter++;
		vertex_iter++;
	}

	glEnd();

	for (auto c = obj->children->begin(); c != obj->children->end(); c++)
	{
		SceneGraphManager::RenderObject(&(*c));
	}

	glPopMatrix();
}

void SceneGraphManager::RenderObjectVBO(Object *obj)
{
	glPushMatrix();

	glMultMatrixf(obj->transformation->data);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if(obj->gfx->material->texture != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, obj->gfx->material->texture->texID);
	}

	glMaterialfv(GL_FRONT, GL_SPECULAR, obj->gfx->material->spec);
	glMaterialf(GL_FRONT, GL_SHININESS, obj->gfx->material->shine);


	glBindBufferARB( GL_ARRAY_BUFFER_ARB, obj->gfx->vboId);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, obj->gfx->cboId);
	glColorPointer( 3, GL_FLOAT, 0, (char *) NULL);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, obj->gfx->tboId );
    glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );				 

	glDrawArrays( GL_TRIANGLES, 0, obj->gfx->vertices->size() );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY);

	for (auto c = obj->children->begin(); c != obj->children->end(); c++)
	{
		SceneGraphManager::RenderObjectVBO(&(*c));
	}

	glPopMatrix();
}*/