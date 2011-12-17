#ifndef ITUENGINE_HEAPALLOCATOR_HPP
#define ITUENGINE_HEAPALLOCATOR_HPP

#include <SDL_stdinc.h>

class HeapAllocator
{
private:
	class HeapMetaData
	{

	};

	void *_root;

public:
	HeapAllocator(Uint32 max_size_bytes);
	~HeapAllocator();

	void *Allocate(Uint32 size_bytes);
	void Deallocate(void *p);
};

#endif ITUENGINE_HEAPALLOCATOR_HPP