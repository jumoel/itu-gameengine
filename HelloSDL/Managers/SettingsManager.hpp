#ifndef ITUENGINE_SETTINGS_MANAGER_H
#define ITUENGINE_SETTINGS_MANAGER_H

#include <Templates/TSingleton.hpp>

class SettingsManager
{
	SINGLETON( SettingsManager )

public:
	float GetSensivity();
	void SetSensivity(float *value);
	float GetMouseInvert();
	void SetMouseInvert(bool *value);

private:
	static float const SETTINGS_SENSIVITY;
	static float const SETTINGS_MOUSE_INVERT;
	float Sensivity;
	float MouseInvert;
};

#endif