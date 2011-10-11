#ifndef ITUENGINE_ENGINE_H
#define ITUENGINE_ENGINE_H

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
	Window *m_Window;
	FPSCalculator *m_FPSCalculator;
	GraphicsSystem *m_Graphics;

	bool m_Running;

	void RunGraphics();
};

#endif