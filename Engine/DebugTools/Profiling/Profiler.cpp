#include "Profiler.h"
#include <cassert>
#include <fstream>

void Profiler::initalize(const char* fileName)
{
	this->fileName = fileName;
	frameIndex = -1;
	categoryIndex = 0;
	numUsedCategories = 0;
}

void Profiler::shutdown()
{
	std::ofstream outStream(fileName, std::ios::trunc);

	//Write category headers
	for (unsigned int i = 0; i < numUsedCategories; i++)
	{
		outStream << categories[i].name;
		outStream << ((i + 1) < numUsedCategories) ? ',' : '\n';
	}

	for (unsigned int frame = 0; frame < frameIndex;frame++)
	{
		for (unsigned int cat = 0; cat < numUsedCategories;cat++)
		{
			outStream << categories[cat].samples[frame];
			outStream << ((cat + 1) < numUsedCategories) ? ',' : '\n';
		}
	}

}

void Profiler::newFrame()
{
	if (frameIndex != -1)
		assert(categoryIndex == numUsedCategories);
	frameIndex++;
	categoryIndex = 0;
}

void Profiler::addEntry(const char* category, float time)
{
	assert(categoryIndex < MAX_PROFILE_CATAGORIES);
	assert(frameIndex < MAX_FRAME_SAMPLES);
	ProfileCategory& pc = categories[categoryIndex++];
	if (frameIndex == 0) 
	{
		pc.name = category;
		numUsedCategories++;
	}
	else
	{
		assert(pc.name == category && category != NULL);
		assert(categoryIndex < numUsedCategories);
	}
	categoryIndex++;
	pc.samples[frameIndex] = time;
}