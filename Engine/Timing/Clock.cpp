#include "Clock.h"
namespace Timing
{
	bool Clock::initialize()
	{
		return false;
	}

	bool Clock::shutdown()
	{
		return false;
	}

	void Clock::newFrame()
	{
	}

	float Clock::timeElapsedLastFrame() const
	{
		return -1;
	}
}