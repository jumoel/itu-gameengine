#ifndef ITUENGINE_ENGINE_H
#define ITUENGINE_ENGINE_H

#include <Managers/SettingsManager.hpp>
#include <Game/FPSCalculator.hpp>
#include <Abstractions/Window.hpp>
#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Managers/EventManager.hpp>
#include <Subsystems/Physics/PhysicsSystem.hpp>
#include <Math/Vector3f.hpp>
#include <Utils/StackAllocator.hpp>

class Engine
{
public:
	void Run();
	void StartUp();
	void ShutDown();
	int mousex;	
	int mousey;
	Vector3f test;
	
	FPSCalculator *GetFPSCalculator() { return m_FPSCalculator; }
	Window *GetWindow() { return m_Window; }
	GraphicsSystem *GetGraphicsSystem() { return m_Graphics; }
	EventManager *GetEventManager() { return m_EventManager; }
	PhysicsSystem *GetPhysicsSystem() { return m_Physics; }

private:
	void handleKeyPress( SDL_KeyboardEvent *key, Uint8 eventtype );
	void handleMouseMove( SDL_MouseMotionEvent *key, Uint8 eventtype);
	void handleMouseButtonPress( SDL_MouseButtonEvent *key, Uint8 eventtype);

	SettingsManager *m_SettingsManager;
	Window *m_Window;
	FPSCalculator *m_FPSCalculator;
	GraphicsSystem *m_Graphics;
	PhysicsSystem *m_Physics;
	EventManager *m_EventManager;
	StackAllocator *m_SingleFrameAllocator;

	int lastTime;

	bool m_Running;
};

#endif