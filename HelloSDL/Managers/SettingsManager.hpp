#ifndef ITUENGINE_SETTINGS_MANAGER_H
#define ITUENGINE_SETTINGS_MANAGER_H

#include <Templates/TSingleton.hpp>

class SettingsManager
{
	SINGLETON( SettingsManager )

public:
	// General Functions:
	void Init();
	void SetToDefaults();
	void UpdateXML();
	// Sensivity:
	float GetSensivity();
	void SetSensivity(float *value);
	// Mouse Invert:
	float GetMouseInvertX();
	float GetMouseInvertY();
	void SetMouseInvertX(bool *enabled);
	void SetMouseInvertY(bool *enabled);
	void SetMouseInvertBoth(bool *enabled);

private:
	static float const SETTINGS_SENSIVITY;
	float Sensivity;
	static float const SETTINGS_MOUSE_INVERT;
	float MouseInvertX;
	float MouseInvertY;
};

#endif