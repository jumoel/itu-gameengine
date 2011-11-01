#ifndef ITUENGINE_ENGINE_H
#define ITUENGINE_ENGINE_H

#include <Managers/SettingsManager.hpp>
#include <Game/FPSCalculator.hpp>
#include <Abstractions/Window.hpp>
#include <Subsystems/Graphics/GraphicsSystem.hpp>

class Engine
{
public:
	void Run();
	void StartUp();
	void ShutDown();
	
	FPSCalculator *GetFPSCalculator() { return m_FPSCalculator; }
	Window *GetWindow() { return m_Window; }

private:
	SettingsManager *m_SettingsManager;
	Window *m_Window;
	FPSCalculator *m_FPSCalculator;
	GraphicsSystem *m_Graphics;

	bool m_Running;

	void RunGraphics();
};

#endif