#include "Profiler.h"
#include <cassert>

void Profiler::initalize(const char* fileName)
{
	this->fileName = fileName;
	frameIndex = -1;
	categoryIndex = 0;
}

void Profiler::shutdown()
{

}

void Profiler::newFrame()
{
	frameIndex++;
	categoryIndex = 0;
}

void Profiler::addEntry(const char* category, float time)
{
	ProfileCatagory& pc = categories[categoryIndex++];
	if (frameIndex == 0)
		pc.name = category;
	else
		assert(pc.name == category);
	pc.samples[frameIndex] = time;

}