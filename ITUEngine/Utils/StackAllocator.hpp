#ifndef ITUENGINE_STACK_ALLOCATOR_H
#define ITUENGINE_STACK_ALLOCATOR_H

#include <SDL_stdinc.h>

class StackAllocator
{
public:
	typedef Uint32 Marker;

	explicit StackAllocator(Uint32 stackSize_bytes);
	~StackAllocator();

	void* Allocate(Uint32 size_bytes);
	Marker GetMarker();
	void FreeToMarker(Marker marker);
	void Clear();

private:
	Marker Root;
	Marker Current;
};

#endif
