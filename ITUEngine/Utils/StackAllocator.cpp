#include <Utils/StackAllocator.hpp>
#include <Utils/MemorySizes.hpp>

StackAllocator::StackAllocator(Uint32 stackSize_bytes)
{
	// Constructs a stack allocator with the given total size.
	// That is, mallocs ALOT, which is then converted into a local stack.
	Root = (Marker)malloc(stackSize_bytes);
	Current = Root;
}

StackAllocator::~StackAllocator()
{
	// All of the memory should be freed, everything destroyed... and such.
	// That is, all of the virtual stack is freed.
	free((void*)Root);
}

Uint32 StackAllocator::GetMemoryUsage()
{
	return ((Uint32) Current - (Uint32) Root);
}

void* StackAllocator::Allocate(Uint32 size_bytes)
{
	// Allocates a new block of the given size from stack top.
	Marker temp = Current;
	Current += size_bytes;
	
	return (void*)temp;
}


StackAllocator::Marker StackAllocator::GetMarker()
{
	// Returns a marker to the current stack top.
	return Current;
}

void StackAllocator::FreeToMarker(Marker marker)
{
	// Rolls the stack back to a previous marker.
	Current = marker;
}

void StackAllocator::Clear()
{
	
	// Clears the entire stack (rolls the stack back to zero).
	Current = Root;
}
