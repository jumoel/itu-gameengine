#ifndef ITUENGINE_TIME_H
#define ITUENGINE_TIME_H

#include <SDL.h>
#include <stdint.h>

class Time
{
public:
	static uint32_t GetCurrentMS()
	{
		return SDL_GetTicks();
	}
};

#endif