#include "boundingbox.h"

boundingbox::boundingbox() {}
boundingbox::boundingbox(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {}

boundingbox::boundingbox(const point3& a, const point3& b)
{
	x = interval(std::fmin(a.x, b.x), std::fmax(a.x, b.x));
	y = interval(std::fmin(a.y, b.y), std::fmax(a.y, b.y));
	z = interval(std::fmin(a.z, b.z), std::fmax(a.z, b.z));
}

boundingbox::boundingbox(const boundingbox& box1, const boundingbox& box2)
{
	x = interval(box1.x, box2.x);
	y = interval(box1.y, box2.y);
	z = interval(box1.z, box2.z);
}

const interval& boundingbox::axisInterval(const int& n) const
{
	if (n == 0) return x;
	else if (n == 1) return y;
	else return z;
}

bool boundingbox::hit(const ray& r, interval& rayT) const
{
	for (int axis = 0; axis < 3; axis++)
	{
		const interval& ax = axisInterval(axis);
		const double adinv = 1.0 / r.direction[axis];

		double intersection1 = (ax.min - r.origin[axis]) * adinv;
		double intersection2 = (ax.max - r.origin[axis]) * adinv;

		if (intersection1 < intersection2)
		{
			if (intersection1 > rayT.min) rayT.min = intersection1;
			if (intersection2 < rayT.max) rayT.max = intersection2;
		}
		else
		{
			if (intersection2 > rayT.min) rayT.min = intersection2;
			if (intersection1 < rayT.max) rayT.max = intersection1;
		}

		if (rayT.max <= rayT.min) return false;
	}

	return true;
}