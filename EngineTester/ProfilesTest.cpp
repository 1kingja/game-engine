#include <gtest\gtest.h>
#include <DebugTools\Profiling\Profiler.h>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;

string getNextToken(ifstream& theFile)
{
	char c;
	string ret;
	while (theFile.good())
	{
		theFile >> c;
		if (c == ',' || c == '\n' )
			break;
		ret += c;
	}
	return ret;
}


TEST(Profiler, SampleProfiles)
{
	char* categories[]=
	{
		"Catagory1",
		"Catagory2",
		"Catagory3"
	};
	const unsigned int NUM_CATEGORIES = sizeof(categories)/sizeof(*categories);

	Profiler profiler;
	const char* profileFileName = "profiles.csv";
	profiler.initalize(profileFileName);

	const unsigned int NUM_FRAMES = 5;

	float sampleNumber = 0;
	for (float frame = 0; frame < NUM_FRAMES; frame++)
	{
		profiler.newFrame();
		for (unsigned int cat = 0; cat < NUM_CATEGORIES;cat++)
		profiler.addEntry(categories[cat], sampleNumber++);
	}
	profiler.shutdown();

	ifstream input(profileFileName);

	EXPECT_EQ(getNextToken(input), "Catagory1");
	EXPECT_EQ(getNextToken(input), "Catagory2");
	EXPECT_EQ(getNextToken(input), "Catagory3");
	for (unsigned int i = 0; i < (NUM_FRAMES*NUM_CATEGORIES); i++)
	{
		string buf = getNextToken(input);
		EXPECT_EQ(atoi(buf.c_str()), i);
	}
}