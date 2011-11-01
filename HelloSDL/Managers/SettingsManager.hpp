#ifndef ITUENGINE_SETTINGS_MANAGER_H
#define ITUENGINE_SETTINGS_MANAGER_H

#include <Templates/TSingleton.hpp>

class SettingsManager
{
public:
	SettingsManager() {}
	~SettingsManager() {}
	// General Functions:
	void StartUp();
	void SetToDefaults();
	void UpdateXML();
	// Sensivity:
	float GetSensivity();
	void SetSensivity(float *value);
	// Mouse Invert:
	float GetMouseInvertX();
	float GetMouseInvertY();
	void SetMouseInvertX(bool enabled);
	void SetMouseInvertY(bool enabled);
	void SetMouseInvertBoth(bool enabled);

private:
	static bool const SETTINGS_SENSIVITY;
	float Sensivity;
	static bool const SETTINGS_MOUSE_INVERT;
	bool MouseInvertX;
	bool MouseInvertY;
};

#endif