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

	float length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	float lengthSq() const
	{
		return (x * x + y * y + z * z);
	}
};

// Handle reversed vector multiplication
inline vector3 operator *(const float n, const vector3 v)
{
	return v * n;
}

int main()
{

	return 0;
}