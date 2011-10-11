#include <Managers/Engine.hpp>

#include <Abstractions/Time.hpp>
#include <Game/FPSCalculator.hpp>
#include <Subsystems/Graphics/GraphicsSystem.hpp>

void Engine::Run()
{
	m_Running = true;

	SDL_Event event;

	while (m_Running)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				m_Running = false;
				break;

			case SDL_VIDEORESIZE:
				GetWindow()->Resize(event.resize.w, event.resize.h);

				break;
			/*
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handleKeyPress(&event.key, event.type);
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handleMouseButtonPress(&event.button, event.type);
				break;

			case SDL_MOUSEMOTION:
				handleMouseMove(&event.motion, event.type);
				break;
			*/
			default:
				break;
			}
		}

		// Calculate and show FPS in title bar
		m_FPSCalculator->SetCurrentTime(Time::GetCurrentMS());

		char title[15];
		sprintf_s(title,"FPS: %d", m_FPSCalculator->GetFPS());
		m_Window->SetWindowTitle(title);

		// Display the graphics
		m_Graphics->Render();
	}
}

void Engine::RunGraphics()
{

}

void Engine::StartUp()
{
	m_Window = new Window();
	m_Window->StartUp();

	m_Graphics = new GraphicsSystem();
	m_Graphics->StartUp();

	m_FPSCalculator = new FPSCalculator();
	m_FPSCalculator->StartUp();

	m_Running = false;
}

void Engine::ShutDown()
{
	m_Running = false;

	m_FPSCalculator->ShutDown();

	m_Graphics->ShutDown();

	m_Window->ShutDown();
}