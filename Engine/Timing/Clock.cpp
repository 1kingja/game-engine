#include "Clock.h"
namespace Timing
{
	bool Clock::initialize()
	{
		bool b = QueryPerformanceFrequency;
		if ( ! b)
			return false;
		return QueryPerformanceCounter(&timeLastFrame);
	}
	bool Clock::shutdown() { return true; }

	void Clock::newFrame()
	{
		LARGE_INTEGER thisTime;
		QueryPerformanceCounter(&thisTime);
		LARGE_INTEGER delta; 
		delta.QuadPart = thisTime.QuadPart - timeLastFrame.QuadPart;
		deltaTime = ((float)delta.QuadPart) / timeFrequency.QuadPart;
		timeLastFrame.QuadPart = thisTime.QuadPart;
	}

	float Clock::timeElapsedLastFrame() const
	{
		return deltaTime;
	}
}