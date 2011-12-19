#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Managers/MediaManager.hpp>
#include <Managers/LightingManager.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>
#include <Assertion.hpp>
#include <Utils/ShaderUtils.hpp>
#include <SDL.h>
#include "GL/glew.h"
#include "GL/wglew.h"
#include <Game/Camera.hpp>
#include <Game/PathPlanner.hpp>
#include <Game/HUD.hpp>



void GraphicsSystem::StartUp()
{
	this->InitOpenGL();
	SINGLETONINSTANCE(MediaManager)->StartUp();

	m_SceneGraph = createGraph();
	
}

void GraphicsSystem::InitOpenGL()
{
	//Enable textures
	glEnable(GL_TEXTURE_2D);

	//Enable lighting
	SINGLETONINSTANCE(LightingManager)->Init();

	//Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	/*set reflective properties */
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the backgroundColor*/
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );


	glEnable( GL_DEPTH_TEST );

	glDepthFunc( GL_LEQUAL );
	glDepthMask(GL_TRUE);

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}


void GraphicsSystem::RenderRecursive(Object *obj)
{
	glPushMatrix();
	glMultMatrixf(obj->transformation->data);
	if(obj->model != NULL)
	{
		obj->model->Render();
	}
	
	for (auto it = obj->children->begin(); it != obj->children->end(); ++it)
	{
		RenderRecursive(&(*it));
	}
	glPopMatrix();
}


void GraphicsSystem::Render()
{
	// Clear the window
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	

	Camera *CameraObject = m_SceneGraph->m_CameraObject;

	gluLookAt(
		CameraObject->Position.x(), CameraObject->Position.y(), CameraObject->Position.z(), 
		CameraObject->LookAt.x(), CameraObject->LookAt.y(), CameraObject->LookAt.z(), 
		CameraObject->Up.x(), CameraObject->Up.y(), CameraObject->Up.z()
		);

	RenderRecursive(m_SceneGraph->m_RootNode);

	SDL_ShowCursor(1);

	HUD::draw();

	SDL_GL_SwapBuffers();
}

void GraphicsSystem::ShutDown()
{
	SINGLETONINSTANCE(MediaManager)->ShutDown();
	delete m_SceneGraph;
}