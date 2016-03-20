#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H

class __declspec(dllexport) Profiler
{
public:
	void addEntry(const char* category, float time);
	void newFrame();
	void initalize(const char* fileName);
	void shutdown();
};

#endif