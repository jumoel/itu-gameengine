#include <Managers/Engine.hpp>
#include <Globals.hpp>
//Engine *g_Engine;

#include <crtdbg.h>

int main(int argc, char **argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	g_Engine = new Engine();

	g_Engine->StartUp();

	g_Engine->Run();

	g_Engine->ShutDown();

	return 0;
}