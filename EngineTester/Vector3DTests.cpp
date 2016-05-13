#include <gtest\gtest.h>
#include <Math\Constants.h>
#include <Math\Vector3D.h>
#include <Misc\TypeDefs.h>
using Math::Vector3D;
using uint;

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

TEST(Vector3D, MagnitudeSquared)
{
	Vector3D ourVector(3, 4, 5);
	EXPECT_FLOAT_EQ(ourVector.magnitudeSquared(), 50.0f);

	Vector3D ourVector2(0, 6, 0);
	EXPECT_FLOAT_EQ(ourVector2.magnitudeSquared(), 36.0f);
}

TEST(Vector3D, Normalization)
{
	Vector3D vec(1.0f, 2.0f, 3.0f);
	Vector3D normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, 0.26726124191242438468455348087975f);
	EXPECT_FLOAT_EQ(normalized.y, 0.53452248382484876936910696175951f);
	EXPECT_FLOAT_EQ(normalized.z, 0.80178372573727315405366044263926f);

	vec = Vector3D(-2.8f, 8.4f, -3.14f);
	normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, -0.2980417151042440347087515078823f);
	EXPECT_FLOAT_EQ(normalized.y, 0.89412514531273210412625452364691f);
	EXPECT_FLOAT_EQ(normalized.z, -0.3342324947954736674948141909823f);
}

void testProjectionAlgorithms(
	const Vector3D& source,
	const Vector3D& target)
{
	Vector3D targetNormalized = target.normalized();
	Vector3D oldResult = source.dot(targetNormalized) * targetNormalized;
	Vector3D newResult = source.projectOnto(target);
	EXPECT_FLOAT_EQ(oldResult.x, newResult.x);
	EXPECT_FLOAT_EQ(oldResult.y, newResult.y);
	EXPECT_FLOAT_EQ(oldResult.z, newResult.z);
}

TEST(Vector3D, projectOnto)
{
	Vector3D source(2, 4);
	Vector3D target(1, 0);
	Vector3D result = source.projectOnto(target);
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
	EXPECT_FLOAT_EQ(result.z, 0.0f);

	Vector3D vectors[] =
	{
	Vector3D(1.0f, 2.0f, 3.0f),
	Vector3D(4.8f, 9.1f, 5.6f),
	Vector3D(0.0f, 5.0f, 0.0f),
	Vector3D(-3.2f, -4.9f, 6.7f),
	Vector3D(2.4f, 3.1f, -99.6f),

	};
	const uint NUM_VECTORS = sizeof(vectors) / sizeof(*vectors);
	for(uint i = 0; i < NUM_VECTORS - 1; i++)
	{
		testProjectionAlgorithms(vectors[i], vectors[i + 1]);
		testProjectionAlgorithms(vectors[i + 1], vectors[i]);
	}

	Vector3D a(0.5f, sqrt(3.0f) / 2);
	Vector3D b(sqrt(3.0f) / 2.0f, 0.5f);
	float dotResult = a.dot(b);
	EXPECT_FLOAT_EQ(dotResult, cos(Math::PI / 6.0f));

}

TEST(Vector3D, lerp)
{
	Vector3D source(4.7f, 9.2f, 7.1f);
	Vector3D target(7.4f, 2.9f, 1.7f);
	Vector3D difference = target - source; 
	float alpha = 0.0f;
	while(alpha <= 1.0f)
	{
		Vector3D lerpResult1 = lerp(alpha, source, target);
		Vector3D lerpResult2 = source + alpha * difference;
		EXPECT_FLOAT_EQ(lerpResult1.x, lerpResult2.x);
		EXPECT_FLOAT_EQ(lerpResult1.y, lerpResult2.y);
		EXPECT_FLOAT_EQ(lerpResult1.z, lerpResult2.z);
		alpha += 0.01f;
	}
}