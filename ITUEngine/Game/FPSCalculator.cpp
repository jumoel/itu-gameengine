#include <Game/FPSCalculator.hpp>

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

void FPSCalculator::StartUp()
{
	ticks = 0;
	LastTime = 0;
	LastReturnedTime = 0;
	FPSSaved = 0;
}

void FPSCalculator::ShutDown()
{
}
