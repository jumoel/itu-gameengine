#include <iostream>
#include <fstream>

#include <Managers/MemoryManager.hpp>

/* 
 * Basic functions
 */
void MemoryManager::StartUp(Uint32 stackSize_bytes)
{
	// Constructs a stack allocator with the given total size.
	// That is, alloc(ALOT), which is then converted into a local stack.
}

void MemoryManager::ShutDown()
{
	// All of the memory should be freed, everything destroyed... and such.
	// That is, all of the virtual stack is freed.
	this->Clear();
}

/* 
 * MemoryManager specific functions
 */
void* MemoryManager::Allocate(Uint32 size_bytes)
{
	// Allocates a new block of the given size from stack top.
}

/*
Marker MemoryManager::GetMarker()
{
	// Returns a marker to the current stack top.
}
*/
void MemoryManager::FreeToMarker(Marker marker)
{
	// Rolls the stack back to a previous marker.
}

void MemoryManager::Clear()
{
	// Clears the entire stack (rolls the stack back to zero).
}
