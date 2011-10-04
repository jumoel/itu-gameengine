#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Game/SceneData.hpp>

void GraphicsSystem::StartUp()
{
	m_SceneGraph = createGraph();
}

void GraphicsSystem::ShutDown()
{

}