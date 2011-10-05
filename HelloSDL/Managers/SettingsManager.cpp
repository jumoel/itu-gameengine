#include "SettingsManager.h"

static float const SETTINGS_SENSIVITY = 1.0f;
static float const SETTINGS_MOUSE_INVERT = 1.0f;

float Sensivity = SETTINGS_SENSIVITY;
float MouseInvert = SETTINGS_MOUSE_INVERT;

float SettingsManager::GetSensivity() 
{
	return this->Sensivity;
}

void SettingsManager::SetSensivity(float *value) 
{
	this->Sensivity = *value;
}

float SettingsManager::GetMouseInvert() 
{
	return this->MouseInvert;
}

void SettingsManager::SetMouseInvert(bool *value) 
{
	if (&value)
		this->MouseInvert = 1.0f;
	else
		this->MouseInvert = -1.0f;
}