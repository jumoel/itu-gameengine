#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>

void GraphicsSystem::StartUp()
{
	m_SceneGraph = createGraph();
	m_VectorList = new std::vector<Vector3f>();

	AddToVBORecursive(m_SceneGraph->RootNode, m_VectorList);

	for (auto it = m_VectorList->begin(); it != m_VectorList->end(); ++it)
	{
		std::cout << "(" << it->x() << ", " << it->y() << ", " << it->z() << ")" << std::endl;
	}
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