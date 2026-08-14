#include "boundingbox.h"

boundingbox::boundingbox() {}
boundingbox::boundingbox(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {}

boundingbox::boundingbox(const point3& a, const point3& b)
{
	x = interval(std::fmin(a.x, b.x), std::fmax(a.x, b.x));
	y = interval(std::fmin(a.y, b.y), std::fmax(a.y, b.y));
	z = interval(std::fmin(a.z, b.z), std::fmax(a.z, b.z));
}

const interval& boundingbox::axisInterval(int& n) const
{
	if (n == 0) return x;
	else if (n == 1) return y;
	else return z;
}