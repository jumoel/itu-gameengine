#ifndef ITUENGINE_SETTINGS_MANAGER_H
#define ITUENGINE_SETTINGS_MANAGER_H

#include <Templates/TSingleton.hpp>
#include <ThirdParty/pugixml/pugixml.hpp>
#include <string>

class SettingsManager
{
public:
	SettingsManager() {}
	~SettingsManager() {}

	void StartUp();
	void ShutDown();

	void SetToDefaults();
	void SaveXML();

	std::string GetOption(std::string identifier);

	void GetRawTree();

private:
	pugi::xml_document doc;
	static bool const SETTINGS_SENSIVITY;
	float Sensivity;
	static bool const SETTINGS_MOUSE_INVERT;
	bool MouseInvertX;
	bool MouseInvertY;
};

#endif