#ifndef ITUENGINE_TIME_H
#define ITUENGINE_TIME_H

#include <SDL.h>

class Time
{
public:
	static int GetCurrentMS()
	{
		return SDL_GetTicks();
	}
};

#endif