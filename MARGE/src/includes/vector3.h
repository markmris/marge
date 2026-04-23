#pragma once

struct vector3
{
	float x, y, z;

	vector3();
	vector3(float x, float y, float z);

	vector3 operator +(const vector3 &v) const;
	vector3 operator -(const vector3 &v) const;
	vector3 operator *(const float &n) const;
	vector3 operator /(const float &n) const;

	vector3 normalized(const vector3 &v) const;

	float magnitude() const;
	float magnitudeSqr() const;
};

inline vector3 operator *(const float &n, const vector3 &v);

float dot(const vector3& v1, const vector3& v2);

vector3 cross(const vector3 &a, const vector3 &b);