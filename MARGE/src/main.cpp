#include <iostream>
#include <cmath>
#include <vector>
#include "includes/vector3.h"
#include "includes/color.h"
#include "includes/ray.h"

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upward, Negative Y downward, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backward
*/

double spherehit(const point3& position, double radius, const ray& r)
{
	vector3 oc = position - r.origin;
	auto a = r.direction.magnitudeSqr();
	auto b = dot(r.direction, oc);
	auto c = oc.magnitudeSqr() - radius * radius;
	auto discriminant = b * b - a * c;
	
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (b - std::sqrt(discriminant)) / a;
	}
}

color3 rayColor(const ray& r)
{
	auto dist = spherehit(point3(0, 0, 1), 0.5, r);

	if (dist > 0.0)
	{
		vector3 normal = normalized(r.at(dist) - vector3(0, 0, 1));
		
		return 0.65 * color3(normal.x + 1, normal.y + 1, normal.z + 1);
	}

	vector3 rayDir = normalized(r.direction);
	auto a = 0.5 * (rayDir.y + 1.0);
	return (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);
}

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
	double viewportWidth = viewportHeight * (double(imageWidth) / double(imageHeight));
	vector3 viewportX(viewportWidth, 0, 0);
	vector3 viewportY(0, -viewportHeight, 0);
	vector3 pixelDeltaX = viewportX / imageWidth;
	vector3 pixelDeltaY = viewportY / imageHeight;

	// Viewport Origin Calculation and Definition
	point3 viewportUpperLeft = (cameraPoint + vector3(0, 0, focalLength)) - (viewportX / 2) - (viewportY / 2);
	point3 viewportOrigin = viewportUpperLeft + (0.5 * (pixelDeltaX + pixelDeltaY));

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int i = 0; i < imageHeight; i++)
	{
		std::clog << "\rScanlines remaining" << (imageHeight - i) << std::flush;

		for (int j = 0; j < imageWidth; j++)
		{
			point3 pixelCenter = viewportOrigin + (i * pixelDeltaY) + (j * pixelDeltaX);
			vector3 rayDirection = pixelCenter - cameraPoint;
			ray raycast(cameraPoint, rayDirection);

			writecolor(std::cout, rayColor(raycast));
		}
	}
	
	std::clog << "\r----------------------DONE----------------------\n";

	return 0;
}