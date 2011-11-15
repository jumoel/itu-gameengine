#include <Managers/Engine.hpp>

#include <Abstractions/Time.hpp>
#include <Game/FPSCalculator.hpp>
#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Utils/StringUtils.hpp>
#include <Events/EventData/EventData.hpp>
#include <Events/Interfaces/IEventManager.hpp>
#include <Events/Interfaces/IEventData.hpp>

void Engine::Run()
{
	m_Running = true;

	SDL_Event event;
	const EventType keydown("keydownEvent");

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
			
			case SDL_KEYDOWN:
				safeTriggerEvent( EventData<SDL_KeyboardEvent>(event.key, keydown) );
				break;

				//handleKeyPress(&event.key, event.type);
				
			/*
			case SDL_KEYUP:


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

	} // while(m_Running)
}

void Engine::StartUp()
{
	m_SettingsManager = new SettingsManager();
	m_SettingsManager->StartUp();

	m_EventManager = new EventManager();
	m_EventManager->StartUp("Global event manager", true);

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

	m_EventManager->ShutDown();

	m_SettingsManager->ShutDown();
}