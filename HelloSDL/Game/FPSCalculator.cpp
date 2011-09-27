#include "FPSCalculator.h"

FPSCalculator::FPSCalculator() : ticks(), LastTime(0), LastReturnedTime(0), FPSSaved(0)
{
}

FPSCalculator::~FPSCalculator()
{
}

void FPSCalculator::SetCurrentTime(Uint32 CurrentTime)
{
	if ((CurrentTime - LastReturnedTime) > 1000)
	{
		FPSSaved = ticks;
		ticks = 0;
		LastReturnedTime = CurrentTime;
	}

	ticks++;
	LastTime = CurrentTime;
}

int FPSCalculator::GetFPS()
{
	return FPSSaved;
}

void FPSCalculator::SetFPSTitle()
{
	char str[128];
	sprintf(str, "FPS: %d", GetFPS());

	SDL_WM_SetCaption(str, "");
}