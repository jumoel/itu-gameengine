#include "FPSCalculator.h"

FPSCalculator::FPSCalculator() : DtBuffer(), LastTime(0), LastReturnedTime(0), FPSSaved(0.0f), DtBufferIndex(0)
{
}

FPSCalculator::~FPSCalculator()
{
}

void FPSCalculator::SetCurrentTime(Uint32 CurrentTime)
{
	Uint32 dt = CurrentTime - LastTime;

	DtBuffer[(DtBufferIndex++ % DT_BUFFER_LENGTH)] = dt;

	LastTime = CurrentTime;

	if ((CurrentTime - LastReturnedTime) > DT_RETURN_FPS_EVERY)
	{
		LastReturnedTime = CurrentTime;

		float avg = 0.0f;

		for (int i = 0; i < DT_BUFFER_LENGTH; i++)
		{
			avg += (float) DtBuffer[i];
		}

		avg = avg / (float)DT_BUFFER_LENGTH;

		this->FPSSaved = 1.0f / ( avg / 1000.0f);
	}
}

float FPSCalculator::GetFPS()
{
	return FPSSaved;
}

void FPSCalculator::SetFPSTitle()
{
	char str[128];
	sprintf(str, "FPS: %.2f", GetFPS());

	SDL_WM_SetCaption(str, "");
}