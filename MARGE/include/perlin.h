#pragma once

#include "ray.h"

struct perlin
{
	inline static constexpr int pointCount = 256;
	double randDouble[pointCount];
	int permX[pointCount];
	int permY[pointCount];
	int permZ[pointCount];

	perlin();

	double noise(const point3& point) const;
	static void generatePerm(int* p);
	static void permute(int* p, int n);
};