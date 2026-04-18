#include <iostream>
#include <cmath>
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

vector3 cross(const vector3 &a, const vector3 &b) {
	return vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

int main()
{
	int width = 800;
	int height = 800;

	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) 
		{
			std::clog << "\rScanlines remaining" << (height - j) << std::flush;

			auto r = float(j) / (width - 1);
			auto g = float(i) / (height - 1);
			auto b = 0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	std::clog << "\rDONE----------------------\n";

	return 0;
}