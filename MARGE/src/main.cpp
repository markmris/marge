#include <iostream>
#include <cmath>
#include <vector>
#include "includes/vector3.h"

int main()
{
	int width = 800;
	int height = 800;

	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) 
		{
			std::clog << "\rScanlines remaining" << (height - j) << std::flush;

			auto r = float(j) / (width - 1);
			auto g = float(i) / (height - 1);
			auto b = 0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	std::clog << "\r----------------------DONE----------------------\n";

	return 0;
}