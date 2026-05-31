#pragma once

#include <ostream>

struct vector3
{
	double x, y, z;

	vector3();
	vector3(double x, double y, double z);

	vector3 operator +(const vector3 &v) const;
	vector3 operator -(const vector3 &v) const;
	vector3 operator *(const double &n) const;
	vector3 operator /(const double &n) const;

	double magnitude() const;
	double magnitudeSqr() const;
};

vector3 normalized(const vector3& v);

vector3 operator *(const double &n, const vector3 &v);

std::ostream& operator<<(const std::ostream& out, const vector3 &v);

double dot(const vector3& v1, const vector3& v2);

vector3 cross(const vector3 &a, const vector3 &b);