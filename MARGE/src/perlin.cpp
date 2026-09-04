#include "perlin.h"
#include "marge.h"

perlin::perlin()
{
	for (double d : randDouble)
	{
		d = randomDouble();
	}

	generatePerm(permX);
	generatePerm(permY);
	generatePerm(permZ);
}

double perlin::noise(const point3& point) const
{
	int x = int(4 * point.x) & 255;
	int y = int(4 * point.y) & 255;
	int z = int(4 * point.z) & 255;

	return randDouble[permX[x] ^ permY[y] ^ permZ[z]];
}

void perlin::generatePerm(int* p)
{
	for (int i = 0; i < pointCount; i++)
	{
		p[i] = i;
	}

	permute(p, pointCount);
}

void perlin::permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = randomInt(0, 1);
		int temp = p[i];
		p[i] = p[target];
		p[target] = temp;
	}
}