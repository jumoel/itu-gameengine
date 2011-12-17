#include <Utils/ReferenceCounter.hpp>

int ReferenceCounter::AddReference()
{
	_count += 1;

	return _count;
}

int ReferenceCounter::Release()
{
	_count -= 1;

	return _count;
}