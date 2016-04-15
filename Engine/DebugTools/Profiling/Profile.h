#ifndef DEBUG_PROFILE_H 
#define DEBUG_PROFILE_H 
#include <Timing\Clock.h>

namespace Profiling
{

	class __declspec(dllexport) Profile
	{
		Timing::Clock clock;
		const char* category;
	public:
		Profile(const char* category);
		~Profile();
	};
}
#endif 
