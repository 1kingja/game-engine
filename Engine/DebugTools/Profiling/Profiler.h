#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H

class __declspec(dllexport) Profiler
{
public:
	static const unsigned int MAX_FRAME_SAMPLES = 5;
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
	void writeData() const;
	void writeFrame(unsigned int frameNumber) const;
	char getDelimiter(unsigned int index) const;
	bool wrapped() const;
public:
	void initalize(const char* fileName);
	void shutdown();
	void newFrame();
	void addEntry(const char* category, float time);
};

#endif