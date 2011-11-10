#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>

void GraphicsSystem::StartUp()
{
	m_SceneGraph = createGraph();
	m_VectorList = new std::vector<Vector3f>();

	AddToVBORecursive(m_SceneGraph->RootNode, m_VectorList);

	// The four below lines needs to be commented out to work for Emil, QQ. Need to research!
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VectorList), m_VectorList, GL_STATIC_DRAW);

	// Black background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapBuffers();
}

void GraphicsSystem::ShutDown()
{

}