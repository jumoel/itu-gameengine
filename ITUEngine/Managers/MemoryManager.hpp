#ifndef ITUENGINE_MEMORY_MANAGER_H
#define ITUENGINE_MEMORY_MANAGER_H

#include <Templates/TSingleton.hpp>

class MemoryManager
{
	SINGLETON( MemoryManager )

public:

	void StartUp();
	void ShutDown();

	// Not yet implemented.
	void Allocate();
	void Free();
};

#endif
