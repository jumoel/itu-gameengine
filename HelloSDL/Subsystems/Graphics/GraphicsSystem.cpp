#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>

void GraphicsSystem::StartUp()
{
	m_SceneGraph = createGraph();
	m_VectorList = new std::vector<Vector3f>();

	GLuint vba_id;
	glGenVertexArrays(1, &vba_id);

	// The two below lines needs to be commented out to work for Emil, QQ. Need to research!
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	AddToVBORecursive(m_SceneGraph->RootNode, m_VectorList);


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

}

void GraphicsSystem::ShutDown()
{

}