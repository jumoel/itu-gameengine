#include "SceneGraphManager.h"
#include "SDL.h"
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

	auto color_iter = obj->colors->begin();
	auto vertex_iter = obj->vertices->begin();

	glBegin(GL_TRIANGLES);

	while (color_iter != obj->colors->end() && vertex_iter != obj->vertices->end())
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

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, obj->vboId);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, obj->cboId);
	glColorPointer( 3, GL_FLOAT, 0, (char *) NULL);

	glDrawArrays( GL_TRIANGLES, 0, obj->vertices->size() );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );

	for (auto c = obj->children->begin(); c != obj->children->end(); c++)
	{
		SceneGraphManager::RenderObjectVBO(&(*c));
	}

	glPopMatrix();
}