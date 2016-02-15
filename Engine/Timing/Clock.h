#ifndef  ENGINE_CLOCK_H
#define ENGINE_CLOCK_H
#include <Windows.h>

namespace Timing
{
	class __declspec(dllexport) Clock
	{
		LARGE_INTEGER timeFrequency;
		LARGE_INTEGER timeLastFrame;
		LARGE_INTEGER deltaLastFrame;
		float deltaTime;
	public:
		bool initialize();
		bool shutdown();
		void newFrame();
		float timeElapsedLastFrame() const;
	};
}

#endif 
