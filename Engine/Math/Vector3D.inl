Vector3D& Vector3D::operator +=(const Vector3D& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

float Vector3D::dot(const Vector3D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3D::magnitude() const
{
	return sqrt(magnitudeSquared());
}

float Vector3D::magnitudeSquared() const
{
	return this->dot(*this);
}

Vector3D Vector3D::normalized() const
{
	float inverseMagnitude = 1.0f / magnitude();
	return inverseMagnitude * (*this);
}

Vector3D Vector3D::perpCwXy() const
{
	return Vector3D(y, -x);
}
Vector3D Vector3D::perpCcwXy() const
{
	return Vector3D(-y, x);
}

Vector3D Vector3D::projectOnto(const Vector3D& target) const
{
	return (this->dot(target) / target.magnitudeSquared()) * target;
}

Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z);
}

Vector3D operator-(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z);
}

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

 Vector3D lerp(float alpha, const Vector3D& source, const Vector3D& target)
 {
	 return (1.0f - alpha) * source + alpha * target;
 }
