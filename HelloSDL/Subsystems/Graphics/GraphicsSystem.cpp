#include <Subsystems/Graphics/GraphicsSystem.h>
#include <Game/SceneData.hpp>

void GraphicsSystem::StartUp()
{
	m_SceneGraph = createGraph();
}

void GraphicsSystem::ShutDown()
{

}