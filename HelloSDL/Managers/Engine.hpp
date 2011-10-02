#ifndef ITUENGINE_ENGINE_H
#define ITUENGINE_ENGINE_H

#include <Game/FPSCalculator.hpp>
#include <Abstractions/Window.hpp>

class Engine
{
public:
	void Run();
	void StartUp();
	void ShutDown();

	FPSCalculator *GetFPSCalculator();

private:
	Window * m_Window;
	FPSCalculator * m_FPSCalculator;
};

#endif