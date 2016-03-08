#ifndef ENGINE_MATRIX_2D_h
#define ENGINE_MATRIX_2D_h
#include "Math\Vector2D.h"
#include <cmath>

namespace Math
{
	struct Matrix2D
	{
		float r0c0, r0c1;
		float r1c0, r1c1;
		inline explicit Matrix2D(
			float r0c0 = 1, float r0c1 = 0, 
			float r1c0 = 0, float r1c1 = 1);
		inline static Matrix2D rotate(float angleInRadians);
	};

	inline Vector2D operator*(
		const Matrix2D& matrix,
		const Vector2D& vector);

#include "Matrix2D.inl"
}
#endif