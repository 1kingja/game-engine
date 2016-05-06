
Matrix2DH::Matrix2DH(
	float r0c0, float r0c1, float r0c2,
	float r1c0, float r1c1, float r1c2) :
		r0c0(r0c0), r0c1(r0c1), r0c2(r0c2),
		r1c0(r1c0), r1c1(r1c1), r1c2(r1c2) {}

Matrix2DH Matrix2DH::rotateZ(float angleInRadians) 
{
	float cosResult = cos(angleInRadians);
	float sinResult = sin(angleInRadians);
	return Matrix2DH(	
		cosResult, -sinResult,	0,
		sinResult, cosResult,	0);
}

Matrix2DH Matrix2DH::translate(float x, float y)
{
	return Matrix2DH(1, 0, x,
					0, 1, y);
}

Matrix2DH Matrix2DH::scale(float x, float y)
{
	return Matrix2DH(x, 0, 0,
					0, y, 0);
}

Vector3D  operator*(const Matrix2DH& matrix, const Vector3D& right)
{
	return Vector3D(
		matrix.r0c0 * right.x + matrix.r0c1 * right.y + matrix.r0c2 * right.z,
		matrix.r1c0 * right.x + matrix.r1c1 * right.y + matrix.r1c2 * right.z, 
		right.z);
}

Matrix2DH operator*(const Matrix2DH& left, const Matrix2DH& right)
{
	return Matrix2DH(
		left.r0c0 * right.r0c0 + left.r0c1 * right.r1c0,
		left.r0c0 * right.r0c1 + left.r0c1 * right.r1c1,
		left.r0c0 * right.r0c2 + left.r0c1 * right.r1c2 + left.r0c2,

		left.r1c0 * right.r0c0 + left.r1c1 * right.r1c0,
		left.r1c0 * right.r0c1 + left.r1c1 * right.r1c1,
		left.r1c0 * right.r0c2 + left.r1c1 * right.r1c2 + left.r1c2);
}