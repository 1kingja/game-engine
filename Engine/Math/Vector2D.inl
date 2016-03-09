Vector2D& Vector2D::operator +=(const Vector2D& right)
{
	x += right.x;
	y += right.y;
	return *this;
}
Vector2D& Vector2D::operator -=(const Vector2D& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2D operator+(const Vector2D& left, const Vector2D& right)
{
	return Vector2D(left.x + right.x, left.y + right.y);
}

Vector2D operator*(float scalar, const Vector2D& vector)
{
	return Vector2D(scalar * vector.x, scalar * vector.y);
}

Vector2D operator*(const Vector2D& vector, float scalar)
{
	return scalar * vector;
}