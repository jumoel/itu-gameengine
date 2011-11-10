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
	void SaveXML();

	void SetOption(std::string identifier, std::string value);
	void SetOptionToDefault(std::string identifier);
	void SetAllOptionsToDefaults();

	std::string GetOption(std::string identifier);
	std::string GetOptionDefault(std::string identifier);

private:
	pugi::xml_document doc;
};

#endif