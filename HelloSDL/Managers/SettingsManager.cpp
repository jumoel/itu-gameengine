#include <iostream>
#include <string>
#include <vector>

#include <Managers/SettingsManager.hpp>
#include <ThirdParty/pugixml/pugixml.hpp>
#include <Utils/StringUtils.hpp>

// General Functions
void SettingsManager::StartUp()
{
	// Loads the various values from the XML-file.
	pugi::xml_parse_result result = doc.load_file("../HelloSDL/Resources/Settings.xml");
	std::cout << "Importing \"Settings.xml\": " << result.description() << std::endl;

	// Left-over test-lines - also shows usage:
	//std::cout << "Win!: " << this->GetOption("video/resolution/width.default");
	//std::cout << " (video/resolution/width.default)" << std::endl;
	//std::cout << "Fail: " << this->GetOption("video/resolution/smokingheights");
	//std::cout << " (video/resolution/smokingheights)" << std::endl;
}

void SettingsManager::ShutDown() 
{
	this->SaveXML();
	// ...along with some other stuff that should probably happen.
}

void SettingsManager::SaveXML()
{
	// Writes the current settings to the XML-file.
	// In the end, this is probably the only thing ShutDown() should so.
}

// Functions for Setting Option-values.
void SettingsManager::SetOption(std::string identifier)
{
	// Sets a given option to a given value.
}

void SettingsManager::SetOptionToDefault(std::string identifier)
{
	// Sets a given option to its default value.
}

void SettingsManager::SetToDefaults()
{
	// Resets all the variables to their defaults, if available.
}

// Functions for Getting Option-values.
std::string SettingsManager::GetOption(std::string identifier)
{
	// Returns the value of a given option, and "null" if not found.
	// Tokenizes the XML-tree, and scans until only the last token is left.
	std::vector<std::string> tokens = StringUtils::tokenize(identifier, "/");

	auto length = tokens.size();
	auto node = doc.root();
	auto it = tokens.begin();

	for (int i = 0; i < length - 1; i++)
	{
		node = node.child((*it).c_str());
		it++;
	}
	
	// Checks if the last token also has an attribute-value included
	std::string result = (*it).c_str();
	int findPos = result.find(".");
	
	// If found, it is used, otherwise the child's value is picked
	if (findPos != -1) 
		result = node.child(result.substr(0,findPos).c_str()).attribute(result.substr(findPos+1,result.length()).c_str()).value();
	else
		result = node.child_value(result.c_str());

	// Checks if the found value was valid or not
	if (result == "") result = "null";
	
	return result;
}

std::string SettingsManager::GetOptionDefault(std::string identifier)
{
	// Returns the default-value of a given option.
	return this->GetOption(identifier + ".default");
}