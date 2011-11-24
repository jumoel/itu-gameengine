#ifndef ITUENGINE_MEMORY_MANAGER_H
#define ITUENGINE_MEMORY_MANAGER_H

#include <Templates/TSingleton.hpp>
#include <SDL_stdinc.h>

class MemoryManager
{
	SINGLETON( MemoryManager )

public:
	typedef Uint32 Marker;

	void StartUp(Uint32 stackSize_bytes);
	void ShutDown();

	void* Allocate(Uint32 size_bytes);
	// Marker GetMarker();
	void FreeToMarker(Marker marker);
	void Clear();
};

#endif
