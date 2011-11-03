#include <Managers/LightingManager.hpp>
#include <GL/glew.h>
#include <iostream>

void LightingManager::Init()
{
	InputManager::RegisterKeyboardEventHandler(this);

	glEnable(GL_LIGHTING);
	float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	for(int i = 0; i < 8; i++)
	{
		lights[i].lightIndex = i;
	}

}

void LightingManager::SetGlobalAmbientLight(float r, float g, float b, float a)
{
	float global_ambient[] = { r, g, b, a };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

int LightingManager::getAvailableLightIndex()
{
	for(int i = 0; i < 8; i++)
	{
		if(!lights[i].inUse)
		{
			return i;
		}
	}
	std::cout << "Error! No available light" << std::endl;
	return -1;
}

void LightingManager::OnKeyDown(KeyPressedEvent *key)
{
	auto keyInput = key->GetInput();

	if(keyInput->keysym.sym == SDLK_j)
	{
		if(lights[0].inUse)
		{
			lights[0].enable(false);
			std::cout << "Disabling Light0" << std::endl;
		}
		else
		{
			lights[0].enable(true);
			std::cout << "Enabling Light0" << std::endl;
		}
	}

}
