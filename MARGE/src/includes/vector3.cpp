#include <cmath>
#include <ostream>
#include "vector3.h"

vector3::vector3() : x(0), y(0), z(0) {}
vector3::vector3(double x, double y, double z) : x(x), y(y), z(z) {}

vector3 vector3::operator +(const vector3 &v) const
{
	return vector3(x + v.x, y + v.y, z + v.z);
}

vector3 vector3::operator -(const vector3 &v) const
{
	return vector3(x - v.x, y - v.y, z - v.z);
}

vector3 vector3::operator *(const double &n) const
{
	return vector3(x * n, y * n, z * n);
}

vector3 vector3::operator /(const double &n) const
{
	return vector3(x / n, y / n, z / n);
}

vector3 vector3::normalized(const vector3 &v) const
{
	return v / v.magnitude();
}

double vector3::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

double vector3::magnitudeSqr() const
{
	return (x * x + y * y + z * z);
}


// Handle reversed vector multiplication
vector3 operator *(const double &n, const vector3 &v)
{
	return v * n;
}

std::ostream& operator <<(std::ostream& out, const vector3 &v)
{
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

double dot(const vector3& v1, const vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector3 cross(const vector3 &a, const vector3 &b) {
	return vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}