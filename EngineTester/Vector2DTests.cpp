#include <gtest\gtest.h>
#include <Math\Vector2D.h>
using Math::Vector2D;

TEST(Vector2D, Constructor)
{
	Vector2D first(1, 2);
	EXPECT_FLOAT_EQ(1, first.x);
	EXPECT_FLOAT_EQ(2, first.y);

}

TEST(Vector2D, VectorAddition)
{
	Vector2D first(1, 2);
	Vector2D second(3, 4);

	Vector2D result1 = first + second;
	Vector2D result2 = second + first;
	EXPECT_FLOAT_EQ(4, result1.x);
	EXPECT_FLOAT_EQ(6, result1.y);

	EXPECT_FLOAT_EQ(result1.x, result2.x);
	EXPECT_FLOAT_EQ(result1.y, result2.y);
}

TEST(Vector2D, ScalarMultiplication)
{
	Vector2D vec(-7, 3);
	Vector2D result1 = 8 * vec;
	Vector2D result2 = vec * 8;
	
	EXPECT_FLOAT_EQ(result1.x, -56);
	EXPECT_FLOAT_EQ(result1.y, 24);
	EXPECT_FLOAT_EQ(result1.x, result2.x);
	EXPECT_FLOAT_EQ(result1.y, result2.y);
}

TEST(Vector2D, CopyConstructor)
{
	Vector2D source(5, -1234.5678);
	Vector2D theCopy(source);
	EXPECT_FLOAT_EQ(theCopy.x, source.x);
	EXPECT_FLOAT_EQ(theCopy.y, source.y);
}

TEST(Vector2D, AssignmentOperators)
{
	Vector2D source(5, -1234.5678);
	Vector2D another(1, 1);
	EXPECT_FLOAT_EQ(another.x, 1);
	EXPECT_FLOAT_EQ(another.y, 1);
	another = source;
	EXPECT_FLOAT_EQ(another.x, source.x);
	EXPECT_FLOAT_EQ(another.y, source.y);
	EXPECT_FLOAT_EQ(another.x, 5);
	EXPECT_FLOAT_EQ(another.y, -1234.5678);
}

TEST(Vector2D, AssignmentPlusEquals)
{
	Vector2D source(5, -1234.5678);
	Vector2D another(1, 1);
	another += source;
	EXPECT_FLOAT_EQ(another.x, 6);
	EXPECT_FLOAT_EQ(another.y, -1233.5678);
}

TEST(Vector2D, AssignmentMinusEquals)
{
	Vector2D source(5, -1234.5678);
	Vector2D another(1, 1);
	another -= source;
	EXPECT_FLOAT_EQ(another.x, -4);
	EXPECT_FLOAT_EQ(another.y, 1235.5678);
}