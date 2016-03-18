#include <gtest\gtest.h>
#include <DebugTools\Profiling\Profiler.h>

TEST(Profiler, mashedPotatoes)
{
	Profiler profiler;
	profiler.initalize();

	const unsigned int NUM_ENTRIES = 15;

	for (unsigned int i = 0; i < NUM_ENTRIES; i++)
	{
		profiler.newFrame();
		profiler.addEntry("Category1", i);
		profiler.addEntry("Category2", i);
		profiler.addEntry("Category3", i);
	}
	profiler.shutdown();


}