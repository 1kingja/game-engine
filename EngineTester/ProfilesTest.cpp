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
	Profiler profiler;
	const char* profileFileName = "profiles.csv";
	profiler.initalize(profileFileName);

	const unsigned int NUM_ENTRIES = 15;

	for (float i = 0; i < NUM_ENTRIES; i++)
	{
		profiler.newFrame();
		profiler.addEntry("Category1", i);
		profiler.addEntry("Category2", i);
		profiler.addEntry("Category3", i);
	}
	profiler.shutdown();

	ifstream input(profileFileName);

	EXPECT_EQ(getNextToken(input), "Catagory1");
	EXPECT_EQ(getNextToken(input), "Catagory2");
	EXPECT_EQ(getNextToken(input), "Catagory3");
	for (unsigned int i = 0; i < NUM_ENTRIES; i++)
	{
		string buf = getNextToken(input);
		EXPECT_EQ(atoi(buf.c_str()), i);
	}
}