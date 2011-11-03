#include <iostream>
#include <string>
#include <vector>

#include <Managers/SettingsManager.hpp>
#include <ThirdParty/pugixml/pugixml.hpp>
#include <Utils/StringUtils.hpp>

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
	pugi::xml_parse_result result = doc.load_file("../HelloSDL/Resources/Settings.xml");
	std::cout << "Settings.XML Load result: " << result.description() << std::endl;

	// Temporary test-strings:
	std::cout << "Keyboard for EXIT: " << doc.child("controls").child("keyboard").child_value("quit") << std::endl;
	std::cout << "trololol: " << this->GetOption("controls/keyboard/quit");
}

void SettingsManager::ShutDown() {}

void SettingsManager::SetToDefaults()
{
	// Resets all the variables to their defaults, if available.
}

void SettingsManager::SaveXML()
{
	// Writes the current settings to the XML-file.
}

std::string SettingsManager::GetOption(std::string identifier)
{
	std::vector<std::string> tokens = StringUtils::tokenize(identifier, "/");

	auto length = tokens.size();
	auto node = doc.root();
	auto it = tokens.begin();

	for (int i = 0; i < length - 1; i++)
	{
		node = node.child((*it).c_str());
		it++;
	}

	return node.child_value((*it).c_str());
}

void SettingsManager::GetRawTree()
{
	// Should - intentionally - Return the raw tree, to more freely extract data.
	// Usage with following sub-functions:
	// .child("name")			The child with name "name" of the current object.
	// .child_value("name")		The value of the child named "name".
	// .attribute("name")		The attribute called "name" of the given child.
	// .... etc.
}
