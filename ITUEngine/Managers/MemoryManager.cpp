#include <Managers/MemoryManager.hpp>
#include <iostream>
#include <fstream>

/* 
 * Basic functions
 */
void MemoryManager::StartUp()
{
	// Needs a "size" parameter, based on the memory needs to be allocated in the stack.
	// That is, alloc(ALOT), which is then converted into a local stack.
}

void MemoryManager::ShutDown()
{
	// All of the memory should be freed, everything destroyed... and such.
	// That is, all of the virtual stack is freed.
}

/* 
 * MemoryManager specific functions
 */

void MemoryManager::Allocate()
{
	// Needs fitting input-value.
	// Allocates memory from the local MemoryManager-stack,
	// and potentially override already existing "new()"/"alloc()".
}

void MemoryManager::Free()
{
	// Needs fitting input-value.
	// Frees memory from the local MemoryManager-stack,
	// and potentially override already existing "~new()"/"free()".
}