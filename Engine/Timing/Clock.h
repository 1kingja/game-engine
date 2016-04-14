#ifndef  ENGINE_CLOCK_H
#define ENGINE_CLOCK_H
#include <Windows.h>

namespace Timing
{
	class __declspec(dllexport) Clock
	{
		LARGE_INTEGER timeFrequency;
		LARGE_INTEGER lastStartTime;
		LARGE_INTEGER deltaLastLap;
		float deltaTime;
	public:
		bool initialize();
		bool shutdown();
		void start();
		void stop();
		void lap(); //newFrame()
		float lastLapTime() const; //timeElapsedLastFrame()
	};
}

#endif 
