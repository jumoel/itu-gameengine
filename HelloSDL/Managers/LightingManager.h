#ifndef ITUENGINE_LIGHTING_MANAGER_H
#define ITUENGINE_LIGHTING_MANAGER_H

#include <Templates/TSingleton.hpp>
#include <Game/Light.hpp>
#include <Managers/InputManager.hpp>

class LightingManager : public IKeyboardEvent
{
	SINGLETON( LightingManager )

public:
	
	Light lights[8];

	void Init();
	void SetGlobalAmbientLight(float r, float g, float b, float a);

	int getAvailableLightIndex();

protected:
	void OnKeyDown(KeyPressedEvent *key);
	
};

#endif

