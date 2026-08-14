#pragma once

#include "marge.h"

struct boundingbox
{
	interval x, y, z;

	boundingbox();
	boundingbox(const interval& x, const interval& y, const interval& z);
	boundingbox(const point3& a, const point3& b);

	const interval& axisInterval(int& n) const;

	bool hit(const ray& r, interval rayT) const;
};