#include <Managers/Engine.hpp>

#include <Abstractions/Time.hpp>
#include <Game/FPSCalculator.hpp>
#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Utils/StringUtils.hpp>
#include <Events/EventData/EventData.hpp>
#include <Events/Interfaces/IEventManager.hpp>
#include <Events/Interfaces/IEventData.hpp>
#include <Managers/MediaManager.hpp>
#include <Managers/InputManager.hpp>

#include <GetOGLPos.hpp>
#include <Events/Interfaces/IEventManager.hpp>

void Engine::Run()
{
	m_Running = true;

	SDL_Event event;
	const EventType keydown("keydownEvent");


	while (m_Running)
	{
		m_SingleFrameAllocator->Clear();

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
				handleKeyPress(&event.key, event.type);
				break;

				
				
			
			//case SDL_KEYUP:


			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handleMouseButtonPress(&event.button, event.type);
				break;
				
			case SDL_MOUSEMOTION:
				mousex = event.motion.x;
			    mousey = event.motion.y;
				//GetOGLPos testing;
				//test = testing.GetPos(mousex, mousey);
				
				
				handleMouseMove(&event.motion, event.type);
				break;
			
			default:
				break;
			}
		}


		//Process eventQueue
	//	safeProcessEventManager(IEventManager::eConstants::INFINITE);


		//Step the physics system
		m_Physics->Step(1);

		// Display the graphics
		m_Graphics->Render();

		// Calculate and show FPS in title bar
		m_FPSCalculator->SetCurrentTime(Time::GetCurrentMS());

		char *title = new char[sizeof(char) * 50];
		//char *title = (char *)m_SingleFrameAllocator->Allocate(sizeof(char) * 50);
		sprintf_s(title, 50,"FPS: %d, Memory: %d bytes", m_FPSCalculator->GetFPS(), m_SingleFrameAllocator->GetMemoryUsage());
		m_Window->SetWindowTitle(title);

	} // while(m_Running)
}

void Engine::StartUp()
{
	m_Window = new Window();
	m_Window->StartUp();

	m_SettingsManager = new SettingsManager();
	m_SettingsManager->StartUp();

	m_EventManager = new EventManager();
	m_EventManager->StartUp("Global event manager", true);

	//IMPORTANT: Call this before m_Graphics->StartUp()
	m_Physics = SINGLETONINSTANCE(PhysicsSystem);
	m_Physics->StartUp();

	m_Graphics = new GraphicsSystem();
	m_Graphics->StartUp();

	m_FPSCalculator = new FPSCalculator();
	m_FPSCalculator->StartUp();

	m_SingleFrameAllocator = new StackAllocator(GB(1));

	m_Running = false;
}

void Engine::ShutDown()
{
	m_Running = false;

	m_FPSCalculator->ShutDown();

	m_Physics->ShutDown();

	m_Graphics->ShutDown();

	m_EventManager->ShutDown();

	m_SettingsManager->ShutDown();

	m_Window->ShutDown();
}

void Engine::handleKeyPress( SDL_KeyboardEvent *key, Uint8 eventtype )//(SDL_keysym *keysym, Uint8 eventtype )
{
	auto keyEvent = new KeyPressedEvent(key, eventtype);

	if(eventtype == SDL_KEYDOWN)
	{
		if(key->keysym.sym == SDLK_ESCAPE)
		{
			m_Running = false;
			return;
		}

		InputManager::NotifyKeyDown(keyEvent);	
	}
	else if(eventtype == SDL_KEYUP)
	{
		InputManager::NotifyKeyUp(keyEvent);
	}

	delete(keyEvent);
}

void Engine::handleMouseButtonPress( SDL_MouseButtonEvent *key, Uint8 eventtype)
{
	const EventType mouseClickPosition("mouseClickPositionEvent");
	auto mouseButtonEvent = new MouseClickEvent(key, eventtype);

	if(eventtype == SDL_MOUSEBUTTONDOWN)
	{
		InputManager::NotifyButtonDown(mouseButtonEvent);
		auto mouseWorldPos = GetOGLPos::GetPos(key->x, key->y);
		safeTriggerEvent( EventData<Vector3f>(mouseWorldPos, mouseClickPosition) );

	}
	else if(eventtype == SDL_MOUSEBUTTONUP)
	{
		InputManager::NotifyButtonUp(mouseButtonEvent);
	}

	delete mouseButtonEvent;
}

void Engine::handleMouseMove( SDL_MouseMotionEvent *key, Uint8 eventtype)
{
	auto mouseMoveEvent = new MouseMoveEvent(key, eventtype);

	if(eventtype == SDL_MOUSEMOTION)
	{
		InputManager::NotifyMotion(mouseMoveEvent);
	}
	
	delete mouseMoveEvent;
}