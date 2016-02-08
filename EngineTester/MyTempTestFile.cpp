#include <gtest\gtest.h>

TEST(MyArbitraryCategoryName, MyArbitraryTestName)
{
	int i = 7;
	int j = 10;
	int asdfasdf = i * j;
	EXPECT_EQ(60, asdfasdf);
	EXPECT_TRUE(asdfasdf == 90);
}

TEST(MyArbitraryCategoryName, SomeOtherTestName) 
{

}