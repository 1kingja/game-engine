#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H
#include <Misc\TypeDefs.h>

namespace Profiling
{
	class __declspec(dllexport) Profiler
	{
	public:
		static const je::uint MAX_FRAME_SAMPLES = 1000;
		static Profiler& getInstance();
	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler theInstance;
#if PROFILING_ON
		const char* fileName;
		static const je::uint MAX_PROFILE_CATAGORIES = 20;
		je::uint frameIndex;
		je::uint categoryIndex;
		je::uint numUsedCategories;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATAGORIES];
		void writeData() const;
		void writeFrame(je::uint frameNumber) const;
		char getDelimiter(je::uint index) const;
		bool currentFrameComplete() const;
		bool wrapped() const;
#endif
	public:
#if PROFILING_ON
		void initalize(const char* fileName);
		void shutdown();
		void newFrame();
		void addEntry(const char* category, float time);
#else
		void initalize(const char* fileName) {}
		void shutdown() {}
		void newFrame() {}
		void addEntry(const char* category, float time) {}
#endif
	};

#define profiler Profiling::Profiler::getInstance()
}
#endif