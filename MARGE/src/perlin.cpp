#include "perlin.h"
#include "marge.h"

perlin::perlin()
{
	for (double& d : randDouble)
	{
		d = randomDouble();
	}

	generatePerm(permX);
	generatePerm(permY);
	generatePerm(permZ);
}

double perlin::noise(const point3& point) const
{
	double horizontal = point.x - std::floor(point.x);
	double vertical = point.y - std::floor(point.y);
	double width = point.z - std::floor(point.z);
	horizontal = horizontal * horizontal * (3 - 2 * horizontal);
	vertical = vertical * vertical * (3 - 2 * vertical);
	width = width * width * (3 - 2 * width);

	int x = int(std::floor(point.x));
	int y = int(std::floor(point.y));
	int z = int(std::floor(point.z));

	double c[2][2][2];

	for (int dx = 0; dx < 2; dx++)
	{
		for (int dy = 0; dy < 2; dy++)
		{
			for (int dz = 0; dz < 2; dz++)
			{
				c[dx][dy][dz] = randDouble[
					permX[(x + dx) & 255] ^
					permY[(y + dy) & 255] ^
					permZ[(z + dz) & 255]
				];
			}
		}
	}

	return trilerp(c, horizontal, vertical, width);
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
		int target = randomInt(0, i);
		int temp = p[i];
		p[i] = p[target];
		p[target] = temp;
	}
}

double perlin::trilerp(double c[2][2][2], double horizontalCoord, double verticalCoord, double width)
{
	double accumulation = 0.0;

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < 2; z++)
			{
				accumulation +=
					(x * horizontalCoord + (1 - x) * (1 - horizontalCoord)) *
					(y * verticalCoord + (1 - y) * (1 - verticalCoord)) *
					(z * width + (1 - z) * (1 - width)) *
					c[x][y][z];
			}
		}
	}

	return accumulation;
}