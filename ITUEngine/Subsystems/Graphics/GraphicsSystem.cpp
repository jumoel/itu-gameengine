#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>
#include <Assertion.hpp>

void GraphicsSystem::StartUp()
{
	this->InitOpenGL();

	m_SceneGraph = createGraph();
	m_VectorList = new std::vector<Vector3f>();

	glEnableClientState(GL_VERTEX_ARRAY);

	AddToVBORecursive(m_SceneGraph->RootNode, m_VectorList);

	// The four below lines needs to be commented out to work for Emil, QQ. Need to research!
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VectorList), m_VectorList, GL_STATIC_DRAW);
}

void GraphicsSystem::InitOpenGL()
{
	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the backgroundColor*/
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 1.0f );

	glEnable( GL_DEPTH_TEST );

	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void GraphicsSystem::AddToVBORecursive(Object *obj, std::vector<Vector3f> *vectors)
{
	std::vector<Vector3f> *v_list = obj->gfx->vertices;
	for (auto it = v_list->begin(); it != v_list->end(); ++it)
	{
		vectors->push_back(*it);
	}

	for (auto it = obj->children->begin(); it != obj->children->end(); ++it)
	{
		AddToVBORecursive(&(*it), vectors);
	}
}

void GraphicsSystem::Render()
{
	// Clear the window
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	Camera *CameraObject = m_SceneGraph->CameraObject;

	gluLookAt(
		CameraObject->Position.x(), CameraObject->Position.y(), CameraObject->Position.z(), 
		CameraObject->LookAt.x(), CameraObject->LookAt.y(), CameraObject->LookAt.z(), 
		CameraObject->Up.x(), CameraObject->Up.y(), CameraObject->Up.z()
		);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	// Another "needs to be commented out to work for Emil"-line, QQ. Need to research!
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapBuffers();
}

void GraphicsSystem::ShutDown()
{

}