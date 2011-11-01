#include <Managers/SettingsManager.hpp>
#include <ThirdParty/pugixml/pugixml.hpp>
#include <iostream>

// Depending on how the XML-import works, these variables might disappear.
static bool const SETTINGS_SENSIVITY = 1.0f;
static bool const SETTINGS_MOUSE_INVERT = false;
float Sensivity = SETTINGS_SENSIVITY;
bool MouseInvertX = SETTINGS_MOUSE_INVERT;
bool MouseInvertY = SETTINGS_MOUSE_INVERT;

// General Functions
void SettingsManager::StartUp()
{
	// Loads the various values from the XML-file.
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../HelloSDL/Resources/Settings.xml");

	// Test strings printing out info from the XML-file:
	std::cout << "Load result: " << result.description() << std::endl;
	std::cout << "Keyboard for EXIT: " << doc.child("controls").child("keyboard").child_value("quit") << std::endl;
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
	if(this->MouseInvertX)
		return -1.0f;
	else
		return 1.0f;
}

float SettingsManager::GetMouseInvertY() 
{
	if (this->MouseInvertY)
		return -1.0f;
	else
		return 1.0f;
}

void SettingsManager::SetMouseInvertX(bool enabled) 
{
	this->MouseInvertX = enabled;
}

void SettingsManager::SetMouseInvertY(bool enabled) 
{
	this->MouseInvertY = enabled;
}

void SettingsManager::SetMouseInvertBoth(bool enabled)
{
	SetMouseInvertX(enabled);
	SetMouseInvertY(enabled);
}
