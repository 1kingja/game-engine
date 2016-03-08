
Matrix2D::Matrix2D(
	float r0c0, float r0c1,
	float r1c0, float r1c1) :
	r0c0(r0c0), r0c1(r0c1),
	r1c0(r1c0), r1c1(r1c1)
{
}

Matrix2D Matrix2D::rotate(float angleInRadians)
{
	float cosResult = cos(angleInRadians);
	float sinResult = sin(angleInRadians);
	return Matrix2D
		(cosResult, -sinResult,
		sinResult, cosResult);
}


Vector2D operator*(
	const Matrix2D& matrix,
	const Vector2D& vector)
{
	return Vector2D(
		matrix.r0c0 * vector.x+matrix.r0c1 * vector.y,
		matrix.r1c0 * vector.x+matrix.r1c1 * vector.y);
}