#include <iostream>
#include <cmath>
#include <vector>
#include "includes/vector3.h"
#include "includes/color.h"

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

			writecolor(std::cout, vector3(r, g, b));
		}
	}
	
	std::clog << "\r----------------------DONE----------------------\n";

	return 0;
}