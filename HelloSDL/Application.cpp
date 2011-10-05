#include <Managers/Engine.hpp>

Engine *g_Engine;

int main(int argc, char **argv)
{
	g_Engine = new Engine();

	g_Engine->StartUp();

	g_Engine->Run();

	g_Engine->ShutDown();

	return 0;
}