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
#include <Utils/Profiler.hpp>

#include <GetOGLPos.hpp>
#include <Events/Interfaces/IEventManager.hpp>

#include <Utils/MemorySizes.hpp>

void Engine::Run()
{
	m_Running = true;

	SDL_Event event;
	const EventType keydown("keydownEvent");

	while (m_Running)
	{
		SINGLETONINSTANCE(Profiler)->Begin("ClearSingleFrameAllocator");
		m_SingleFrameAllocator->Clear();
		SINGLETONINSTANCE(Profiler)->End("ClearSingleFrameAllocator");

		SINGLETONINSTANCE(Profiler)->Begin("EventHandling");
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
				threadSafeQueEvent( IEventDataPointer( new EventData<SDL_KeyboardEvent>(event.key, keydown)) );
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
		safeProcessEventQueue(-1);
		SINGLETONINSTANCE(Profiler)->End("EventHandling");

		int currentTime = Time::GetCurrentMS();
		int deltaT = (currentTime - lastTime);

		SINGLETONINSTANCE(Profiler)->Begin("StepPhysics");
		//Step the physics system
		m_Physics->Step(deltaT);
		SINGLETONINSTANCE(Profiler)->End("StepPhysics");

		SINGLETONINSTANCE(Profiler)->Begin("CameraUpdate");
		m_Graphics->m_SceneGraph->m_CameraObject->Update(deltaT);
		SINGLETONINSTANCE(Profiler)->End("CameraUpdate");

		// Display the graphics
		SINGLETONINSTANCE(Profiler)->Begin("Rendering");
		m_Graphics->Render();
		SINGLETONINSTANCE(Profiler)->End("Rendering");

		// Calculate and show FPS in title bar
		m_FPSCalculator->SetCurrentTime(currentTime);

		//char *title = new char[sizeof(char) * 50];
		char *title = (char *)m_SingleFrameAllocator->Allocate(sizeof(char) * 50);
		sprintf_s(title, 50, "FPS: %d, Memory: %d bytes", m_FPSCalculator->GetFPS(), m_SingleFrameAllocator->GetMemoryUsage());
		m_Window->SetWindowTitle(title);

		lastTime = currentTime;

	} // while(m_Running)
}

void Engine::StartUp()
{
	SINGLETONINSTANCE(Profiler)->StartUp();
	SINGLETONINSTANCE(Profiler)->Begin("StartUp");

	lastTime = Time::GetCurrentMS();
	m_Window = new Window();
	m_Window->StartUp();

	m_SettingsManager = new SettingsManager();
	m_SettingsManager->StartUp();

	m_EventManager = new EventManager();
	m_EventManager->StartUp("Global event manager", true);

	//Register useful event types.
	m_EventManager->AddRegisteredEventType( EventType ("keydownEvent") );	
	m_EventManager->AddRegisteredEventType( EventType ("mouseClickPositionEvent") );
	m_EventManager->AddRegisteredEventType( EventType ("mouseClickHUDEvent") );

	//IMPORTANT: Call this before m_Graphics->StartUp()
	m_Physics = SINGLETONINSTANCE(PhysicsSystem);
	m_Physics->StartUp();

	m_Graphics = new GraphicsSystem();
	m_Graphics->StartUp();

	m_FPSCalculator = new FPSCalculator();
	m_FPSCalculator->StartUp();

	m_SingleFrameAllocator = new StackAllocator(MB(100));

	m_Running = false;

	SINGLETONINSTANCE(Profiler)->End("StartUp");
}

void Engine::ShutDown()
{
	m_Running = false;
	SINGLETONINSTANCE(Profiler)->Begin("ShutDown");

	delete m_SingleFrameAllocator;

	m_FPSCalculator->ShutDown();

	m_Physics->ShutDown();

	m_Graphics->ShutDown();

	m_EventManager->ShutDown();

	m_SettingsManager->ShutDown();

	m_Window->ShutDown();

	SINGLETONINSTANCE(Profiler)->End("ShutDown");
	SINGLETONINSTANCE(Profiler)->ShutDown();
}

void Engine::handleKeyPress( SDL_KeyboardEvent *key, Uint8 eventtype )//(SDL_keysym *keysym, Uint8 eventtype )
{
	auto keyEvent = new KeyPressedEvent(key, eventtype);

	if(eventtype == SDL_KEYDOWN)
	{
		if(key->keysym.sym == SDLK_ESCAPE)
		{
			m_Running = false;

			delete keyEvent;
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
	const EventType mouseWorldClickPosition("mouseClickPositionEvent");
	const EventType mouseHUDClickPosition("mouseClickHUDEvent");

	auto mouseButtonEvent = new MouseClickEvent(key, eventtype);

	if(eventtype == SDL_MOUSEBUTTONDOWN)
	{
		InputManager::NotifyButtonDown(mouseButtonEvent);
		auto mouseWorldPos = GetOGLPos::GetPos(key->x, key->y);
		if (mouseWorldPos.z() < 35.0f)
		{
			threadSafeQueEvent( IEventDataPointer(new EventData<Vector3f>(mouseWorldPos, mouseWorldClickPosition)) );
		} 
		else 
		{
			threadSafeQueEvent( IEventDataPointer(new EventData<Vector3f>(mouseWorldPos, mouseHUDClickPosition)) );
		}

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