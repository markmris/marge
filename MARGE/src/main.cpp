#include <iostream>
#include <vector>

struct vector3
{
	float x, y, z;

	vector3() : x(0), y(0), z(0) {}
	vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	vector3 operator +(const vector3 &v) const
	{
		return vector3(x + v.x, y + v.y, z + v.z);
	}

	vector3 operator -(const vector3 &v) const
	{
		return vector3(x - v.x, y - v.y, z - v.z);
	}

	vector3 operator *(const float &n) const
	{
		return vector3(x * n, y * n, z * n);
	}

	vector3 operator /(const float &n) const
	{
		return vector3(x / n, y / n, z / n);
	}

	vector3 normalized(const vector3 &v) const
	{
		return v / v.magnitude();
	}

	float magnitude() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	float magnitudeSqr() const
	{
		return (x * x + y * y + z * z);
	}
};

// Handle reversed vector multiplication
inline vector3 operator *(const float n, const vector3 v)
{
	return v * n;
}

float dot(const vector3& v1, const vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

int main()
{

	return 0;
}