#ifndef DEBUG_PROFILE_H 
#define DEBUG_PROFILE_H 
#if PROFILING_ON
#include <Timing\Clock.h>
#endif // PROFILING_ON

namespace Profiling
{
	class __declspec(dllexport) Profile
	{
#if PROFILING_ON
		Timing::Clock clock;
		const char* category;
#endif // PROFILING_ON
	public:
#if PROFILING_ON
		Profile(const char* category);
		~Profile();
#else
		Profile(const char* category) {}
		~Profile() {}
#endif // PROFILING_ON
	};
}

#define PROFILE(category) Profiling::Profile p(category);

#endif 
