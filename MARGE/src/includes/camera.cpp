#include "camera.h"
#include "material.h"
#include <algorithm>

void camera::initialize()
{
	pixelSamplesScale = 1.0 / maxPixelSamples;

	imageHeight = int(imageWidth / aspectRatio);
	imageHeight = std::max(1, imageHeight);

	focalLength = 1.0;

	vup = vector3(0, 1, 0);
	pitch = std::clamp(pitch, -89.999, 89.999);
	pitchRad = degAsRad(pitch);
	yawRad = degAsRad(yaw);

	forward.x = std::cos(pitchRad) * std::sin(yawRad);
	forward.y = std::sin(pitchRad);
	forward.z = std::cos(pitchRad) * std::cos(yawRad);
	forward = normalized(forward);
	localRight = normalized(cross(vup, forward));
	localUp = cross(forward, localRight);

	auto theta = degAsRad(fov);
	auto height = std::tan(theta/2);

	viewportHeight = 2 * height * focalLength;
	viewportWidth = viewportHeight * (double(imageWidth) / double(imageHeight));
	viewportX = viewportWidth * localRight;
	viewportY = -viewportHeight * localUp;
	pixelDeltaX = viewportX / imageWidth;
	pixelDeltaY = viewportY / imageHeight;
	viewportUpperLeft = (cameraPoint + focalLength * forward) - (viewportX / 2) - (viewportY / 2);
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
				pixelColor = rayColor(r, maxDepth, world) + pixelColor;
			}
			
			writeColor(std::cout, pixelColor * pixelSamplesScale);
		}
	}

	std::clog << "\r---------------------- DONE ----------------------\n";
}

color3 camera::rayColor(const ray& r, const int& depth, const hittable& world) const
{
	if (depth <= 0)
		return color3(0, 0, 0);

	hitdata hd;

	if (world.hit(r, interval(0.002, infinity), hd))
	{
		ray scattered;
		color3 attenuation;

		if (hd.material->scatter(r, hd, attenuation, scattered))
			return attenuation * rayColor(scattered, depth - 1, world);

		return color3(0, 0, 0);
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