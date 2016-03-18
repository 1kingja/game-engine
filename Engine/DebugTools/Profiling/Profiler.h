#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H

class Profiler
{
public:
	void addEntry(const char* category, float time);
	void newFrame();
	void shutdown();
	void initalize();
};

#endif