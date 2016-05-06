#ifndef ENGINE_MATRIX_3D_h
#define ENGINE_MATRIX_3D_h
#include "Vector3D.h"
#include <cmath>

namespace Math
{
	struct Matrix3D
	{
		float r0c0, r0c1, r0c2;
		float r1c0, r1c1, r1c2;
		float r2c0, r2c1, r2c2;
		Matrix3D(
			float r0c0 = 1, float r0c1 = 0, float r0c2 = 0,
			float r1c0 = 0, float r1c1 = 1, float r1c2 = 0,
			float r2c0 = 0, float r2c1 = 0, float r2c2 = 1);
		inline static Matrix3D rotateZ(float angleInRadians);
		inline static Matrix3D translate(float x, float y);
		inline static Matrix3D scale(float x, float y);
	};

	inline Vector3D  operator*(const Matrix3D& matrix, const Vector3D& right);
	inline Matrix3D  operator*(const Matrix3D& left, const Matrix3D& right);

#include "Matrix3D.inl"
}

#endif