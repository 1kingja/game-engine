#include <gtest\gtest.h>
#include <DebugTools\Profiling\Profiler.h>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;

namespace
{
	Profiler profiler;

	char* categories[] =
	{
		"Catagory1",
		"Catagory2",
		"Catagory3"
	};
	const char* const PROFILE_FILE_NAME = "profiles.csv";
	const unsigned int NUM_CATEGORIES = sizeof(categories) / sizeof(*categories);

	string getNextToken(ifstream& theFile)
	{
		char c;
		string ret;
		while (theFile.good())
		{
			theFile >> std::noskipws;
			theFile >> c;
			if (c == ',' || c == '\n')
				break;
			ret += c;
		}
		return ret;
	}

	bool isAtEndOfFile(ifstream& input)
	{
		if (!input.good())
			return false;
		char bitBucket;
		input >> bitBucket;
		return !input.good();
	}

	void writeFrames(unsigned int numFrames)
	{
		float sampleNumber = 0;
		for (float frame = 0; frame < numFrames; frame++)
		{
			profiler.newFrame();
			for (unsigned int cat = 0; cat < NUM_CATEGORIES; cat++)
				profiler.addEntry(categories[cat], sampleNumber++);
		}
	}

	void checkFrames(unsigned int numFrames)
	{
		ifstream input(PROFILE_FILE_NAME);

		EXPECT_EQ(getNextToken(input), "Catagory1");
		EXPECT_EQ(getNextToken(input), "Catagory2");
		EXPECT_EQ(getNextToken(input), "Catagory3");
		for (unsigned int i = 0; i < (numFrames*NUM_CATEGORIES); i++)
		{
			string buf = getNextToken(input);
			EXPECT_EQ(atoi(buf.c_str()), i);
		}
		EXPECT_TRUE(isAtEndOfFile(input));
	}

	void runTestsOnFrames(unsigned int numFrames)
	{
		profiler.initalize(PROFILE_FILE_NAME);
		writeFrames(numFrames);
		profiler.shutdown();
		checkFrames(numFrames);
	}

	TEST(Profiler, SmallAmountOfFrames)
	{
		profiler.initalize(PROFILE_FILE_NAME);
		const unsigned int NUM_FRAMES_THIS_TEST = 5;
		writeFrames(NUM_FRAMES_THIS_TEST);
		profiler.shutdown();
		checkFrames(NUM_FRAMES_THIS_TEST);
	}

	TEST(Profile, LargeAmuntOfFramesNonCircular)
	{
		const unsigned int NUM_FRAMES_THIS_TEST = 
			static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * .8);
		writeFrames(NUM_FRAMES_THIS_TEST);
		checkFrames(NUM_FRAMES_THIS_TEST);
	}

	TEST(Profile, ArrayBoundaries)
	{
		const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES;
		writeFrames(NUM_FRAMES_THIS_TEST);
		checkFrames(NUM_FRAMES_THIS_TEST);

		/*const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES + 1;
		writeFrames(NUM_FRAMES_THIS_TEST);
		checkFrames(NUM_FRAMES_THIS_TEST);

		const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES + 2;
		writeFrames(NUM_FRAMES_THIS_TEST);
		checkFrames(NUM_FRAMES_THIS_TEST);*/
	}

	TEST(Profile, CirculatingOnePlusSum)
	{
		/*const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES * 1.5;
		writeFrames(NUM_FRAMES_THIS_TEST);
		checkFrames(NUM_FRAMES_THIS_TEST);*/
	}

	TEST(Profile, GoAroundSeveralTimes)
	{
		/*const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES * 3.141592134234;
		writeFrames(NUM_FRAMES_THIS_TEST);
		checkFrames(NUM_FRAMES_THIS_TEST);*/
	}

	TEST(Profiler, ExcludeIncompleteFrames)
	{
		profiler.initalize(PROFILE_FILE_NAME);
		const unsigned int NUM_FRAMES_THIS_TEST = 5;
		writeFrames(NUM_FRAMES_THIS_TEST);
		profiler.newFrame();
		profiler.addEntry(categories[0], 15);
		profiler.shutdown();
		checkFrames(NUM_FRAMES_THIS_TEST);

		profiler.initalize(PROFILE_FILE_NAME);
		writeFrames(NUM_FRAMES_THIS_TEST);
		profiler.newFrame();
		profiler.addEntry(categories[0], 15);
		profiler.addEntry(categories[1], 16);
		profiler.shutdown();

		checkFrames(NUM_FRAMES_THIS_TEST);
	}

}