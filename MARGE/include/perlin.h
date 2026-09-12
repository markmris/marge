#pragma once

#include "ray.h"

struct perlin
{
	inline static constexpr int pointCount = 256;
	vector3 randomVectors[pointCount];
	int permX[pointCount];
	int permY[pointCount];
	int permZ[pointCount];

	perlin();

	double noise(const point3& point) const;
	static void generatePerm(int* p);
	static void permute(int* p, int n);
	static double perlinlerp(const vector3 c[2][2][2], double horizontalCoord, double verticalCoord, double width);
};