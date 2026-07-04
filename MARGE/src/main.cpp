#include "includes/marge.h"
#include "includes/hittable.h"
#include "includes/objects.h"
#include "includes/objectlists.h"

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upward, Negative Y downward, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backward
*/

color3 rayColor(const ray& r, const hittable& world)
{
	hitdata hd;

	if (world.hit(r, 0, infinity, hd))
	{
		return 0.5 * (hd.normal + color3(1, 0, 1));
	}

	vector3 normalDirection = normalized(r.direction);
	auto a = 0.5 * (normalDirection.y + 1.0);
	return (1.0 - a) * color3(1, 1, 1) + a*color3(0.5, 0.7, 1.0);
}

int main()
{	
	// Camera
	point3 cameraPoint = point3(0, 0, 0);
	double focalLength = 1.0;

	// Image Dimensions
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

	objectlist world;

	world.add(make_shared<sphere>(point3(0.8, 0.2, 2), 0.5));
	world.add(make_shared<sphere>(point3(0.6, -0.3, 1), 0.25));
	world.add(make_shared<sphere>(point3(1, -1, 1), 0.25));

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int i = 0; i < imageHeight; i++)
	{
		std::clog << "\rScanlines remaining" << (imageHeight - i) << std::flush;

		for (int j = 0; j < imageWidth; j++)
		{
			point3 pixelCenter = viewportOrigin + (i * pixelDeltaY) + (j * pixelDeltaX);
			vector3 rayDirection = pixelCenter - cameraPoint;
			ray raycast(cameraPoint, rayDirection);

			writecolor(std::cout, rayColor(raycast, world));
		}
	}
	
	std::clog << "\r---------------------- DONE ----------------------\n";

	return 0;
}