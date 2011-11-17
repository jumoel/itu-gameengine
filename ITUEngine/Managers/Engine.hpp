#ifndef ITUENGINE_ENGINE_H
#define ITUENGINE_ENGINE_H

#include <Managers/SettingsManager.hpp>
#include <Game/FPSCalculator.hpp>
#include <Abstractions/Window.hpp>
#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Managers/EventManager.hpp>

class Engine
{
public:
	void Run();
	void StartUp();
	void ShutDown();
	int mousex;
	int mousey;
	
	FPSCalculator *GetFPSCalculator() { return m_FPSCalculator; }
	Window *GetWindow() { return m_Window; }
	GraphicsSystem *GetGraphicsSystem() { return m_Graphics; }
	EventManager *GetEventManager() { return m_EventManager; }

private:
	SettingsManager *m_SettingsManager;
	Window *m_Window;
	FPSCalculator *m_FPSCalculator;
	GraphicsSystem *m_Graphics;
	EventManager *m_EventManager;

	bool m_Running;
};

#endif