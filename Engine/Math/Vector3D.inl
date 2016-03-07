
Vector3D operator*(float scalar, const Vector3D& vector)
{
	return Vector3D(
		scalar * vector.x,
		scalar * vector.y,
		scalar * vector.z );
}

Vector3D operator*(const Vector3D& vector, float scalar)
{
	return scalar * vector;
}