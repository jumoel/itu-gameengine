#include <Managers/SettingsManager.hpp>

// Depending on how MiniXML works, these variables might possibly disappear.
static float const SETTINGS_SENSIVITY = 1.0f;
static float const SETTINGS_MOUSE_INVERT = 1.0f; // 1.0f means DISABLED!

float Sensivity = SETTINGS_SENSIVITY;
float MouseInvertX = SETTINGS_MOUSE_INVERT;
float MouseInvertY = SETTINGS_MOUSE_INVERT;

// General Functions
void SettingsManager::Init()
{
	// Loads the various values from the XML-file.
}

void SettingsManager::SetToDefaults()
{
	// Resets all the variables to their defaults, if available.
}

void SettingsManager::UpdateXML()
{
	// Writes the current settings to the XML-file.
}

// Sensivity
float SettingsManager::GetSensivity() 
{
	return this->Sensivity;
}

void SettingsManager::SetSensivity(float *value) 
{
	this->Sensivity = *value;
}

// MouseInvert
float SettingsManager::GetMouseInvertX() 
{
	return this->MouseInvertX;
}

float SettingsManager::GetMouseInvertY() 
{
	return this->MouseInvertX;
}

void SettingsManager::SetMouseInvertX(bool *enabled) 
{
	if (&enabled)
		this->MouseInvertX = -1.0f;
	else
		this->MouseInvertX = 1.0f;
}

void SettingsManager::SetMouseInvertY(bool *enabled) 
{
	if (&enabled)
		this->MouseInvertY = -1.0f;
	else
		this->MouseInvertY = 1.0f;
}

void SettingsManager::SetMouseInvertBoth(bool *enabled)
{
	SetMouseInvertX(enabled);
	SetMouseInvertY(enabled);
}
