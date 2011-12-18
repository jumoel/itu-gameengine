#include <Managers/SceneGraphManager.hpp>
#include <SDL.h>
//#include "sdl_opengl.h"
#include "GL/glew.h"
#include <iostream>
#include <memory>
#include <Events/EventData/EventData.hpp>
#include <Math/Vector3f.hpp>
#include <Templates/TSingleton.hpp>
#include "MediaManager.hpp"
#include <Subsystems/Physics/PhysicsSystem.hpp>
#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <Abstractions/Time.hpp>

SceneGraphManager::SceneGraphManager(Camera *CameraObject, Object *RootNode) :
	m_CameraObject(CameraObject),
	m_RootNode(RootNode),
	LastTime(0),
	DeltaTime(0)
{
	safeAddListener(EventListenerPointer(this), EventType("mouseClickHUDEvent"));
}

SceneGraphManager::~SceneGraphManager()
{
	delete m_CameraObject;
	DeleteGraph(m_RootNode);
	//delete m_RootNode;
}

void SceneGraphManager::DeleteGraph(Object* node)
{
	if(node->children->size() > 0)
	{
		for (auto it = node->children->begin(); it != node->children->end(); ++it)
		{
			DeleteGraph(&(*it));
		}
	}
	delete node;
}

char const * SceneGraphManager::GetName()
{
	return "SceneGraphManager";
}

bool SceneGraphManager::HandleEvent( IEventData const & event )
{
	shared_ptr<EventData<Vector3f>> data = dynamic_pointer_cast<EventData<Vector3f>, IEventData>(event.Copy());
	auto val = data->GetValue();

	//If inside defined box... DO:

	Rectangle physicsBox(Point(-0.5f, -0.5f), 1.0f, 1.0f);

	auto box = new Object();
	box->Name = "HUDBox";
	box->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	StaticObjectModel* tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box->physicsModel = tempStaticObject;
	box->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);

	srand(Time::GetCurrentMS());
	float x = (float)(rand() % 400) / 10.0f;
	float y = (float)(rand() % 400) / 10.0f;

	box->SetPos2D(x, y);
	box->SetScale(2.0f, 2.0f, 5.0f);

	m_RootNode->children->push_back(*box);

	SINGLETONINSTANCE(PhysicsSystem)->SetStaticPathMap();


	return true;
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