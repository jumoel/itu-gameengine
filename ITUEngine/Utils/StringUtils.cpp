#include <Utils/StringUtils.hpp>

#include <algorithm>
#include <vector>
#include <cctype>

#include <ThirdParty/SuperFastHash.hpp>

unsigned int StringUtils::hash(std::string s)
{
	auto data = StringUtils::toLower(s);
	return SuperFastHash(data.c_str(), data.length());
}

std::string StringUtils::toLower(std::string s)
{
	std::string data;
	data.resize(s.size());

	std::transform(s.begin(), s.end(), data.begin(), ::tolower);

	return data;
}

std::vector<std::string> StringUtils::tokenize(const std::string &str, const std::string &delimiter = " ")
{
	std::vector<std::string> tokens;

	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiter, 0);
	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiter, lastPos);

	while (pos != std::string::npos || lastPos != std::string::npos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiter, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiter, lastPos);
	}

	return tokens;
}