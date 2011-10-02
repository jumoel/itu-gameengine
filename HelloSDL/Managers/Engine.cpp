#include <Managers/Engine.hpp>
#include <Game/FPSCalculator.hpp>

void Engine::Run()
{
}

void Engine::StartUp()
{
	m_Window = new Window();
	m_Window->StartUp();

	m_FPSCalculator = new FPSCalculator();
	m_FPSCalculator->StartUp();
}

void Engine::ShutDown()
{
	m_FPSCalculator->ShutDown();

	m_Window->ShutDown();
}

FPSCalculator * Engine::GetFPSCalculator()
{
	return m_FPSCalculator;
}