#ifndef ITUENGINE_STRINGUTILS_H
#define ITUENGINE_STRINGUTILS_H

#include <ThirdParty/SuperFastHash.hpp>
#include <algorithm>

using std::string;

class StringUtils
{
public:
	static uint32_t hash(std::string s)
	{
		auto data = StringUtils::toLower(s);
		return SuperFastHash(data.c_str(), data.length());
	}

	static std::string toLower(std::string s)
	{
		string data;
		data.resize(s.size());

		std::transform(s.begin(), s.end(), data.begin(), ::tolower);

		return data;
	}
};

#endif // ITUENGINE_STRINGUTILS_H