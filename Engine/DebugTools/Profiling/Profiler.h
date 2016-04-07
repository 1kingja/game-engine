#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H

class __declspec(dllexport) Profiler
{
public:
	static const unsigned int MAX_FRAME_SAMPLES = 1000;
private:
	const char* fileName;
	static const unsigned int MAX_PROFILE_CATAGORIES = 20;
	unsigned int frameIndex;
	unsigned int categoryIndex;
	unsigned int numUsedCategories;
	struct ProfileCategory
	{
		const char* name;
		float samples[MAX_FRAME_SAMPLES];
	} categories[MAX_PROFILE_CATAGORIES];
	char getDelimiter(unsigned int index) const;
public:
	void initalize(const char* fileName);
	void shutdown();
	void newFrame();
	void addEntry(const char* category, float time);
};

#endif