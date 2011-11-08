#ifndef ITUENGINE_STRINGUTILS_H
#define ITUENGINE_STRINGUTILS_H

#include <string>
#include <vector>

class StringUtils
{
public:
	static unsigned int hash(std::string s);

	static std::string toLower(std::string s);

	static std::vector<std::string> tokenize(const std::string &str, const std::string &delimiter);
};

char const * const hashedStringWildcard = "*";

class HashedString
{
public:
	explicit HashedString(char const * const identityString)
		: m_IdentityHash (strcmp(identityString, hashedStringWildcard) == 0 ? 0 : StringUtils::hash(identityString )),
		m_IdentityString (identityString)
	{
	}

	unsigned int GetHashValue() const
	{
		return m_IdentityHash;
	}

	const std::string & GetString() const
	{
		return m_IdentityString;
	}

	bool operator< (HashedString const & compareTo) const
	{
		bool result = (GetHashValue() < compareTo.GetHashValue());
		return result;
	}

	bool operator> (HashedString const & compareTo) const
	{
		bool result = (GetHashValue() > compareTo.GetHashValue());
		return result;
	}

	bool operator== (HashedString const & compareTo) const
	{
		bool result = (GetHashValue() == compareTo.GetHashValue());
		return result;
	}

private:
	unsigned int m_IdentityHash;
	std::string m_IdentityString;

};

#endif // ITUENGINE_STRINGUTILS_H