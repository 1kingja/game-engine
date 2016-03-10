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
}

TEST(Matrix3D, Rotation)
{
	Matrix3D op;
	op = Matrix3D::rotateZ(0);
	EXPECT_FLOAT_EQ(op.r0c0, 1);
	EXPECT_FLOAT_EQ(op.r0c1, 0);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, 0);
	EXPECT_FLOAT_EQ(op.r1c1, 1);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = Matrix3D::rotateZ(Math::PI);
	EXPECT_FLOAT_EQ(op.r0c0, -1);
	EXPECT_TRUE(closeEnough(op.r0c1, 0));
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_TRUE(closeEnough(op.r1c0, 0));
	EXPECT_FLOAT_EQ(op.r1c1, -1);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = Matrix3D::rotateZ(Math::PI / 2);
	EXPECT_TRUE(closeEnough(op.r0c0, 0));
	EXPECT_FLOAT_EQ(op.r0c1, -1);
	EXPECT_FLOAT_EQ(op.r1c0, 1);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_TRUE(closeEnough(op.r1c1, 0));
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = Matrix3D::rotateZ(Math::PI / 4);
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

	op = Matrix3D::rotateZ(-Math::PI / 4);
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	EXPECT_FLOAT_EQ(op.r2c0, 0);
	EXPECT_FLOAT_EQ(op.r2c1, 0);
	EXPECT_FLOAT_EQ(op.r2c2, 1);

	op = Matrix3D::rotateZ(Math::PI / 3);
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

	op = Matrix3D::rotateZ(-Math::PI / 3);
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

TEST(Matrix3D, Translation)
{
	//Matrix3D translator = Matrix3D::translate(4, 8);
	//Vector3D victim(-3, 8);
	//Vector3D victimPrime = translator * victim;
	//EXPECT_FLOAT_EQ(victimPrime.x, 1);
	//EXPECT_FLOAT_EQ(victimPrime.y, 16);
	//EXPECT_FLOAT_EQ(victimPrime.z, 0);

	Matrix3D translator = Matrix3D::translate(1, 0);
	Vector3D victim(0, 3);
	Vector3D victimPrime = translator * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 1);
	EXPECT_FLOAT_EQ(victimPrime.y, 3);
	EXPECT_FLOAT_EQ(victimPrime.z, 0);
}

TEST(Matrix3D, MatrixVectorMultiply)
{
	Matrix3D op(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Vector3D victim(1,
					2,
					3);

	Vector3D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 14);
	EXPECT_FLOAT_EQ(victimPrime.y, 32);
	EXPECT_FLOAT_EQ(victimPrime.z, 50);
}