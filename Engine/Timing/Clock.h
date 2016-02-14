
#ifndef  ENGINE_CLOCK_H
#define ENGINE_CLOCK_H

namespace Timing
{
	class __declspec(dllexport) Clock
	{
	public:
		bool initialize();
		bool shutdown();
		void newFrame();
		float timeElapsedLastFrame() const;
	};
}

#endif 
