#include "camera.h"

void camera::initialize()
{
	cameraPoint = point3(0, 0, 0);
	focalLength = 1.0;

	maxPixelSamples = 0;
	pixelSamplesScale = 1.0 / maxPixelSamples;

	aspectRatio = 16.0 / 9.0;
	imageHeight = int(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	viewportHeight = 2.0;
	viewportWidth = viewportHeight * (double(imageWidth) / double(imageHeight));
	viewportX = vector3(viewportWidth, 0, 0);
	viewportY = vector3(0, -viewportHeight, 0);
	pixelDeltaX = viewportX / imageWidth;
	pixelDeltaY = viewportY / imageHeight;
	viewportUpperLeft = (cameraPoint + vector3(0, 0, focalLength)) - (viewportX / 2) - (viewportY / 2);
	viewportOrigin = viewportUpperLeft + (0.5 * (pixelDeltaX + pixelDeltaY));
}

void camera::render(const hittable& world)
{
	initialize();

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int i = 0; i < imageHeight; i++)
	{
		std::clog << "\rScanlines remaining: " << (imageHeight - i) << std::flush;

		for (int j = 0; j < imageWidth; j++)
		{
			color3 pixelColor(0, 0, 0);

			for (int sample = 0; sample < maxPixelSamples; sample++)
			{
				ray r = getRay(j, i);
				pixelColor = rayColor(r, world) + pixelColor;
			}
			
			writeColor(std::cout, pixelColor * pixelSamplesScale);
		}
	}

	std::clog << "\r---------------------- DONE ----------------------\n";
}

color3 camera::rayColor(const ray& r, const hittable& world) const
{
	hitdata hd;

	if (world.hit(r, interval(0, infinity), hd))
	{
		return 0.5 * (hd.normal + color3(1, 1, 1));
	}

	vector3 normalDirection = normalized(r.direction);
	auto a = 0.5 * (normalDirection.y + 1.0);
	return (1.0 - a) * color3(1, 1, 1) + a * color3(0.5, 0.7, 1.0);
}

ray camera::getRay(int j, int i) const
{
	vector3 offset = samplePixel();
	point3 pixelSample = viewportOrigin + ((j + offset.x) * pixelDeltaX) + ((i + offset.y) * pixelDeltaY);

	point3 rayOrigin = cameraPoint;
	vector3 rayDirection = pixelSample - rayOrigin;

	return ray(rayOrigin, rayDirection);
}

vector3 camera::samplePixel() const
{
	return vector3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}