#ifndef ENGINE_MATRIX_2DH_h
#define ENGINE_MATRIX_2DH_h
#include "Vector3D.h"
#include <cmath>

namespace Math
{
	struct Matrix2DH
	{
		float r0c0, r0c1, r0c2;
		float r1c0, r1c1, r1c2;
		Matrix2DH(
			float r0c0 = 1, float r0c1 = 0, float r0c2 = 0,
			float r1c0 = 0, float r1c1 = 1, float r1c2 = 0);
		inline static Matrix2DH rotateZ(float angleInRadians);
		inline static Matrix2DH translate(float x, float y);
	};

	inline Vector3D  operator*(const Matrix2DH& matrix, const Vector3D& right);
	inline Matrix2DH  operator*(const Matrix2DH& left, const Matrix2DH& right);

#include "Matrix2DH.inl"
}

#endif