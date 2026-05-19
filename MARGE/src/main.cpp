#include <iostream>
#include <cmath>
#include <vector>
#include "includes/vector3.h"
#include "includes/color.h"
#include "includes/ray.h"

color3 rayColor(const ray& r)
{
	return color3(0, 0, 0);
}

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upwards, Negative Y downwards, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backwards
*/

int main()
{
	point3 cameraPoint = point3(0, 0, 0);
	double focalLength = 1.0;

	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 1080;

	int imageHeight = int(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	// Viewport Creation
	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * double(imageWidth/imageHeight);
	vector3 viewportX(viewportWidth, 0, 0);
	vector3 viewportY(0, -viewportHeight, 0);
	vector3 pixelDeltaX = viewportX / imageHeight;
	vector3 pixelDeltaY = viewportY / imageWidth;

	// Viewport Origin Calculation and Definition
	point3 viewportUpperLeft = (cameraPoint + vector3(0, 0, focalLength)) - (viewportX / 2) - (viewportY / 2);
	point3 viewportOrigin = viewportUpperLeft + 0.5 * (pixelDeltaX + pixelDeltaY);

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int i = 0; i < imageHeight; i++)
	{
		std::clog << "\rScanlines remaining" << (imageHeight - i) << std::flush;

		for (int j = 0; j < imageWidth; j++)
		{
			point3 pixelCenter = viewportOrigin + (i * pixelDeltaY) + (j * pixelDeltaX);
			vector3 rayDirection = pixelCenter - cameraPoint;
			ray raycast(pixelCenter, rayDirection);

			writecolor(std::cout, rayColor(raycast));
		}
	}
	
	std::clog << "\r----------------------DONE----------------------\n";

	return 0;
}