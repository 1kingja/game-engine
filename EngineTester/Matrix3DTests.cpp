#include <gtest\gtest.h>
#include <Math\Matrix3D.h>
#include <Math\Vector3D.h>
#include <Math\Constants.h>
#include "HelperFunctions.h"
using Math::Matrix3D;
using Math::Vector3D;

TEST(Matrix3D, Construction)
{
	Matrix3D identity;
	EXPECT_FLOAT_EQ(identity.r0c0, 1);
	EXPECT_FLOAT_EQ(identity.r0c1, 0);
	EXPECT_FLOAT_EQ(identity.r0c2, 0);
	EXPECT_FLOAT_EQ(identity.r1c0, 0);
	EXPECT_FLOAT_EQ(identity.r1c1, 1);
	EXPECT_FLOAT_EQ(identity.r1c2, 0);
	EXPECT_FLOAT_EQ(identity.r2c0, 0);
	EXPECT_FLOAT_EQ(identity.r2c1, 0);
	EXPECT_FLOAT_EQ(identity.r2c2, 1);

	Matrix3D victim(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	EXPECT_FLOAT_EQ(victim.r0c0, 1);
	EXPECT_FLOAT_EQ(victim.r0c1, 2);
	EXPECT_FLOAT_EQ(victim.r0c2, 3);
	EXPECT_FLOAT_EQ(victim.r1c0, 4);
	EXPECT_FLOAT_EQ(victim.r1c1, 5);
	EXPECT_FLOAT_EQ(victim.r1c2, 6);
	EXPECT_FLOAT_EQ(victim.r2c0, 7);
	EXPECT_FLOAT_EQ(victim.r2c1, 8);
	EXPECT_FLOAT_EQ(victim.r2c2, 9);

	Matrix2DH identity;
	EXPECT_FLOAT_EQ(identity.r0c0, 1);
	EXPECT_FLOAT_EQ(identity.r0c1, 0);
	EXPECT_FLOAT_EQ(identity.r0c2, 0);
	EXPECT_FLOAT_EQ(identity.r1c0, 0);
	EXPECT_FLOAT_EQ(identity.r1c1, 1);
	EXPECT_FLOAT_EQ(identity.r1c2, 0);

	Matrix2DH victim(
		1, 2, 3,
		4, 5, 6,);
	EXPECT_FLOAT_EQ(victim.r0c0, 1);
	EXPECT_FLOAT_EQ(victim.r0c1, 2);
	EXPECT_FLOAT_EQ(victim.r0c2, 3);
	EXPECT_FLOAT_EQ(victim.r1c0, 4);
	EXPECT_FLOAT_EQ(victim.r1c1, 5);
	EXPECT_FLOAT_EQ(victim.r1c2, 6);
}

template<class T>
void testRotation()
{
	T op;
	op = T::rotateZ(0);
	EXPECT_FLOAT_EQ(op.r0c0, 1);
	EXPECT_FLOAT_EQ(op.r0c1, 0);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, 0);
	EXPECT_FLOAT_EQ(op.r1c1, 1);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = T::rotateZ(Math::PI);
	EXPECT_FLOAT_EQ(op.r0c0, -1);
	EXPECT_TRUE(closeEnough(op.r0c1, 0));
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_TRUE(closeEnough(op.r1c0, 0));
	EXPECT_FLOAT_EQ(op.r1c1, -1);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = T::rotateZ(Math::PI / 2);
	EXPECT_TRUE(closeEnough(op.r0c0, 0));
	EXPECT_FLOAT_EQ(op.r0c1, -1);
	EXPECT_FLOAT_EQ(op.r1c0, 1);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_TRUE(closeEnough(op.r1c1, 0));
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = T::rotateZ(Math::PI / 4);
	const float sqrt2Over2 = sqrt(2.0f) / 2.0f;
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = T::rotateZ(-Math::PI / 4);
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = T::rotateZ(Math::PI / 3);
	const float sqrt3Over2 = sqrt(3.0f) / 2.0f;
	EXPECT_FLOAT_EQ(op.r0c0, .5);
	EXPECT_FLOAT_EQ(op.r0c1, -sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c1, .5);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = T::rotateZ(-Math::PI / 3);
	EXPECT_FLOAT_EQ(op.r0c0, .5);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c1, .5);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);
}

TEST(Matrix3D, Rotation)
{
	testRotation<Matrix3D>();
	testRotation<Matrix2DH>();
}

template<class T>
void testTranslation()
{
	T translator = T::translate(4, 8);
	Vector3D victim(-3, 8, 1);
	Vector3D victimPrime = translator * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 1);
	EXPECT_FLOAT_EQ(victimPrime.y, 16);
	EXPECT_FLOAT_EQ(victimPrime.z, 1);
}

TEST(Matrix3D, Translation)
{
	testTranslation<Matrix3D>();
	testTranslation<Matrix2DH>();
}

TEST(Matrix3D, MatrixVectorMultiply)
{
	Matrix3D op(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Vector3D victim(1,2,3);

	Vector3D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 14);
	EXPECT_FLOAT_EQ(victimPrime.y, 32);
	EXPECT_FLOAT_EQ(victimPrime.z, 50);

	Matrix2DH op2(
		1, 2, 3,
		4, 5, 6);

	Vector2DH victim(1,2,3);

	Vector3D victimPrime = op2 * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 14);
	EXPECT_FLOAT_EQ(victimPrime.y, 32);
	EXPECT_FLOAT_EQ(victimPrime.z, 3);
}

TEST(Matrix3D, MatrixMatrtixMultiply)
{
	Matrix3D theMatrix(1, 2, 3,
				4, 5, 6,
				7, 8, 9);
	Matrix3D result = theMatrix * theMatrix;
	EXPECT_FLOAT_EQ(result.r0c0, 30);
	EXPECT_FLOAT_EQ(result.r0c1, 36);
	EXPECT_FLOAT_EQ(result.r0c2, 42);

	EXPECT_FLOAT_EQ(result.r1c0, 66);
	EXPECT_FLOAT_EQ(result.r1c1, 81);
	EXPECT_FLOAT_EQ(result.r1c2, 96);

	EXPECT_FLOAT_EQ(result.r2c0, 102);
	EXPECT_FLOAT_EQ(result.r2c1, 126);
	EXPECT_FLOAT_EQ(result.r2c2, 150);

	Matrix2DH theMatrix(1, 2, 3,
						4, 5, 6);
	Matrix3D result = theMatrix * theMatrix;
	EXPECT_FLOAT_EQ(result.r0c0, 30);
	EXPECT_FLOAT_EQ(result.r0c1, 36);
	EXPECT_FLOAT_EQ(result.r0c2, 42);

	EXPECT_FLOAT_EQ(result.r1c0, 66);
	EXPECT_FLOAT_EQ(result.r1c1, 81);
	EXPECT_FLOAT_EQ(result.r1c2, 96);
}