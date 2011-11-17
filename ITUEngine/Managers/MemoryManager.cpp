#include <Managers/MemoryManager.hpp>
#include <iostream>
#include <fstream>

/* 
 * Basic functions
 */
void MemoryManager::StartUp()
{
	// Here, a finite amount of memory needs to be allocated.
}

void MemoryManager::ShutDown()
{
	// All of the memory should be freed, everything destroyed... and such.
}

/* 
 * MemoryManager specific functions
 */

void MemoryManager::Allocate()
{
	// Needs fitting input-value.
	// Allocates memory from the MemoryManager-stack.
}

void MemoryManager::Free()
{
	// Needs fitting input-value.
	// Frees memory from the MemoryManager-stack.
}