#include <iostream>
#include <cmath>
#include <vector>
#include "includes/vector3.h"
#include "includes/color.h"
#include "includes/ray.h"

int main()
{
	auto aspectRatio = 16.0 / 9.0;
	int width = 1080;

	int height = int(width / aspectRatio);
	height = (height < 1) ? 1 : height;

	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int i = 0; i < height; i++)
	{
		std::clog << "\rScanlines remaining" << (height - i) << std::flush;

		for (int j = 0; j < width; j++) 
		{
			auto r = float(j) / (width - 1);
			auto g = float(i) / (height - 1);
			auto b = 0;

			writecolor(std::cout, color3(r, g, b));
		}
	}
	
	std::clog << "\r----------------------DONE----------------------\n";

	return 0;
}