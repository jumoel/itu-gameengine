#ifndef ITUENGINE_STACK_ALLOCATOR_H
#define ITUENGINE_STACK_ALLOCATOR_H

#define _K 1024
#define _M (1024 * _K)
#define _G (1024 * _M)

#define KB(amount) (amount * _K)
#define MB(amount) (amount * _M)
#define GB(amount) (amount * _G)

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
	Uint32 GetMemoryUsage();

	template <class T> T *make_new() { return new (Allocate(sizeof(T))) T(); }
	template <class T, class P1> T *make_new(P1 p1) { return new (Allocate(sizeof(T))) T(p1); }


private:
	Marker Root;
	Marker Current;
};

#endif
