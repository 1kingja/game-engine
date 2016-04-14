#include <gtest\gtest.h>
#include <Timing\Clock.h>
#include <Qt\qtest.h>
#include <Qt\qdebug.h>
#include <iostream>
using std::cout;
using Timing::Clock;

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;
#define OVERNIGHT_TESTS
#ifdef OVERNIGHT_TESTS
	EXPECT_TRUE(clock.initialize());
	QTest::qSleep(1000);
	clock.lap();
	float timedTime = clock.lastLapTime();
	EXPECT_TRUE(0.9f < timedTime);
	EXPECT_TRUE(timedTime < 1.1f);							
	clock.lap();										
	QTest::qSleep(500);
	clock.lap();					
	timedTime = clock.lastLapTime();
	EXPECT_TRUE(0.4f < timedTime);
	EXPECT_TRUE(timedTime < 0.6f);

	const int NUM_TESTS = 10 + rand() % 100;
	const float THRESHOLD = 0.01f;
	for (int i = 0; i < NUM_TESTS; i++)
	{
		std::cout << ".";
		int thisTestTimeMiliseconds = rand() % 10000;
		float thisTestTimeSeconds = thisTestTimeMiliseconds / 1000.0f;
		clock.lap();
		QTest::qSleep(thisTestTimeMiliseconds);
		clock.lap();
		float elapsedSeconds = clock.lastLapTime();
		EXPECT_TRUE((thisTestTimeSeconds - THRESHOLD) < elapsedSeconds);
		EXPECT_TRUE(elapsedSeconds < (thisTestTimeSeconds + THRESHOLD));
	}
#endif

	clock.lap();
	EXPECT_TRUE(clock.shutdown());
}