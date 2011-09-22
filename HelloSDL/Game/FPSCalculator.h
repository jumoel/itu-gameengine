#ifndef ITUENGINE_FPSCALCULATOR_H
#define ITUENGINE_FPSCALCULATOR_H

#define DT_BUFFER_LENGTH 20
#define DT_RETURN_FPS_EVERY (1000)

#include "SDL.h"

class FPSCalculator
{
public:
	FPSCalculator();
	~FPSCalculator();

	void SetCurrentTime(Uint32 CurrentTime);
	float GetFPS();
	void SetFPSTitle();

private:
	Uint32 DtBuffer[DT_BUFFER_LENGTH];
	int DtBufferIndex;
	float FPSSaved;
	Uint32 LastTime;
	Uint32 LastReturnedTime;
};

#endif