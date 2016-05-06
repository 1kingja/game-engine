#include <gtest\gtest.h>
#include <Math\Vector3D.h>
using Math::Vector3D;

TEST(Vector3D, Constructor)
{
	Vector3D instance(-4.3f, 9.1f, 5.0f);
	EXPECT_FLOAT_EQ(instance.x, -4.3f);
	EXPECT_FLOAT_EQ(instance.y, 9.1f);
	EXPECT_FLOAT_EQ(instance.z, 5.0f);

	Vector3D defaultConstructor;
	EXPECT_FLOAT_EQ(defaultConstructor.x, 0.0f);
	EXPECT_FLOAT_EQ(defaultConstructor.y, 0.0f);
	EXPECT_FLOAT_EQ(defaultConstructor.z, 0.0f);
}

TEST(Vector3D, VectorAddition)
{
	Vector3D first(9, -2, 5);
	Vector3D second(-4, 5.4f, 7);
	Vector3D result = first + second;
	EXPECT_FLOAT_EQ(result.x, 5);
	EXPECT_FLOAT_EQ(result.y, 3.4f);
	EXPECT_FLOAT_EQ(result.z, 12);
}

TEST(Vector3D, ScalarMultiplication)
{
	Vector3D instance(1, 2, 3);
	Vector3D multiplied1 = 5 * instance;
	Vector3D multiplied2 = instance * 5;

	EXPECT_FLOAT_EQ(multiplied1.x, 5  );
	EXPECT_FLOAT_EQ(multiplied1.y, 10 );
	EXPECT_FLOAT_EQ(multiplied1.z, 15 );

	EXPECT_FLOAT_EQ(multiplied2.x, multiplied1.x );
	EXPECT_FLOAT_EQ(multiplied2.y, multiplied1.y );
	EXPECT_FLOAT_EQ(multiplied2.z, multiplied1.z );
}
TEST(Vector3D, AssignmentPlusEquals)
{
	Vector3D source(5, -1234.5678f, 763.123f);
	Vector3D another(1, 1, 125.543f);
	another += source;
	EXPECT_FLOAT_EQ(another.x, 6);
	EXPECT_FLOAT_EQ(another.y, -1233.5678f);
	EXPECT_FLOAT_EQ(another.z, 888.666f);
}

TEST(Vector3D, Subtraction)
{
	Vector3D first(8, 3, 9);
	Vector3D second(7, 1, 5);
	Vector3D result = first - second;
	EXPECT_FLOAT_EQ(result.x, 1);
	EXPECT_FLOAT_EQ(result.y, 2);
	EXPECT_FLOAT_EQ(result.z, 4);
	result = second - first;
	EXPECT_FLOAT_EQ(result.x, -1);
	EXPECT_FLOAT_EQ(result.y, -2);
	EXPECT_FLOAT_EQ(result.z, -4);
}

TEST(Vector3D, Perpendicularity)
{
	Vector3D meVector(4, 2);
	Vector3D perpCw = meVector.perpCwXy();
	Vector3D perpCcw = meVector.perpCcwXy();
	EXPECT_FLOAT_EQ(perpCw.x, 2);
	EXPECT_FLOAT_EQ(perpCw.y, -4);
	EXPECT_FLOAT_EQ(perpCcw.x, -2);
	EXPECT_FLOAT_EQ(perpCcw.y, 4);
}

TEST(Vector3D, DotProduct)
{
	Vector3D first(1, 2, 3);
	Vector3D second(4, 5, 6);
	float result = first.dot(second);
	EXPECT_FLOAT_EQ(result, 32);
}

TEST(Vector3D, Magnitude)
{
	Vector3D ourVector(3, 4, 5);
	float magnitude = ourVector.magnitude();
	EXPECT_FLOAT_EQ(magnitude, 7.0710678118654752440084436210485f);
}