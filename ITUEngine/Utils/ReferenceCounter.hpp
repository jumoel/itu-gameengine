#ifndef ITUENGINE_REFERENCECOUNTER_HPP
#define ITUENGINE_REFERENCECOUNTER_HPP

class ReferenceCounter
{
private:
	int _count;

public:
	int AddReference();
	int Release();
}

#endif ITUENGINE_REFERENCECOUNTER_HPP