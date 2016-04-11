#include "Profiler.h"
#include <cassert>
#include <fstream>

static std::ofstream outStream;

void Profiler::initalize(const char* fileName)
{
	this->fileName = fileName;
	frameIndex = -1;
	categoryIndex = 0;
	numUsedCategories = 0;
}

void Profiler::shutdown()
{
	writeData();
}

void Profiler::newFrame()
{
	if (frameIndex > 0)
		assert(categoryIndex == numUsedCategories);
	frameIndex++;
	categoryIndex = 0;
}

void Profiler::addEntry(const char* category, float time)
{
	assert(categoryIndex < MAX_PROFILE_CATAGORIES);
	ProfileCategory& pc = categories[categoryIndex];
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
	pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
}

char Profiler::getDelimiter(unsigned int index) const
{
	return ((index + 1) < numUsedCategories) ? ',' : '\n';
}

bool Profiler::wrapped() const
{
	return frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1;
}

void Profiler::writeData() const
{
	outStream.open(fileName, std::ios::trunc);

	// Write category headers
	for (unsigned int i = 0; i < numUsedCategories; i++)
	{
		outStream << categories[i].name;
		outStream << getDelimiter(i);
	}

	unsigned int endIndex;
	unsigned int startIndex;

	if (wrapped())
	{
		endIndex = frameIndex % MAX_FRAME_SAMPLES;
		startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
		while (startIndex != endIndex)
		{
			writeFrame(startIndex);
			startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
		}
		if(currentFrameComplete())
		writeFrame(startIndex);
	}
	else
	{
		unsigned int numActualFrames = frameIndex;
		if (currentFrameComplete())
			numActualFrames++;
		startIndex = 0;
		endIndex = numActualFrames;
		while (startIndex < endIndex)
			writeFrame(startIndex++);
	}
	outStream.close();
}

bool Profiler::currentFrameComplete() const
{
	return categoryIndex == numUsedCategories;
}

void Profiler::writeFrame(unsigned int frameNumber) const
{
	for (unsigned int cat = 0; cat < numUsedCategories; cat++)
	{
		outStream << categories[cat].samples[frameNumber];
		outStream << getDelimiter(cat);
	}
}