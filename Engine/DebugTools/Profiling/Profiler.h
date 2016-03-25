#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H

class __declspec(dllexport) Profiler
{
	const char* fileName;
	static const unsigned int MAX_FRAME_SAMPLES = 500;
	static const unsigned int MAX_PROFILE_CATAGORIES = 20;
	unsigned int frameIndex;
	unsigned int categoryIndex;
	struct ProfileCatagory
	{
		const char* name;
		float samples[MAX_FRAME_SAMPLES];
	} categories[MAX_PROFILE_CATAGORIES];

public:
	void initalize(const char* fileName);
	void shutdown();
	void newFrame();
	void addEntry(const char* category, float time);
};

#endif