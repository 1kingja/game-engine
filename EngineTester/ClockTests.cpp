#include <gtest\gtest.h>

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	sleep(1000);
	clock.newFrame();
	float timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.9f < timedTime && timedTime < 1.1f);
	clock.newFrame();
	sleep(500);
	clock.newFrame();
	timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.4f < timedTime && timedTime < 0.6f);



	clock.timeElapsedLastFrame();
	EXPECT_TRUE(clock.shutdown());
}