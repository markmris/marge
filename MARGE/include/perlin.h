#pragma once

#include "vector3.h"

struct perlin
{
	inline static constexpr int pointCount = 256;
	double randDouble[pointCount];
	int permX[pointCount];
	int permY[pointCount];
	int permZ[pointCount];

	perlin();

	double noise(const point3& point);
	static void generatePerm(int* p);
	static void permute(int* p, int n);
};