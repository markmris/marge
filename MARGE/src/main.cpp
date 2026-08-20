#include "includes/marge.h"
#include "includes/camera.h"
#include "includes/hittable.h"
#include "includes/objects.h"
#include "includes/objectlists.h"
#include "includes/material.h"
#include "includes/commandline.h"
#include "includes/bvh.h"
#include "includes/texture.h"
#include <fstream>
#include <string>

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upward, Negative Y downward, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backward
*/

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::ofstream outFile("image.ppm");
	std::streambuf* originalBuffer = std::cout.rdbuf();
	std::cout.rdbuf(outFile.rdbuf());

	camera camera;
	camera.cameraPoint = point3(13, 1.5, 3);
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 1080;
	camera.maxPixelSamples = 32;
	camera.maxDepth = 13;
	camera.fov = 90;
	camera.yaw = 0;
	camera.pitch = -45;
	camera.defocusAngle = 0.6;
	camera.focusDistance = 2.5;

	int globalObjectCount = 20;

	try
	{
		bool help = initializeEngine(argc, argv, camera, globalObjectCount);

		if (help)
		{
			std::cout.rdbuf(originalBuffer);
			
			std::cout << helpmessage;

			return 0;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';

		return 0;
	}

	camera.initialize();

	// World Creation
	objectlist world;

	auto checkerTexture = make_shared<checkertexture>(0.3, color3(1, 0.486, 0), color3(.9, .9, .9));

	auto groundMaterial = make_shared<diffuse>(checkerTexture);
	world.add(make_shared<sphere>(point3(0, -1000.5, 1), 1000, groundMaterial));

	hitdata hd;
	ray objectOriginRay = ray(camera.cameraPoint, camera.getForward());
	point3 objectOrigin;

	if (world.hit(objectOriginRay, interval(0.01, infinity), hd))
	{
		objectOrigin = hd.point - normalized(objectOriginRay.direction) * 0.5;
	}
	else
	{
		std::cerr << "Scene generation failed. Please try again. (Maybe you modified pitch/yaw incorrectly?)";
		return 0;
	}

	shared_ptr<material> objectMaterial;

	for (int x = -globalObjectCount / 4; x < globalObjectCount / 4; x++)
	{
		for (int z = -globalObjectCount / 4; z < globalObjectCount / 4; z++)
		{
			double randomMaterial = randomDouble();
			double radius = randomDouble(0.15, 0.35);
			point3 position = point3(objectOrigin.x + x + randomDouble(-0.3, 0.3), radius, objectOrigin.z + z + randomDouble(-0.3, 0.3));

			if (randomMaterial < 0.75) // Diffuse
			{
				color3 albedo = randomColor() * randomColor();
				objectMaterial = make_shared<diffuse>(albedo);
				point3 position2 = position + vector3(0, randomDouble(0, 0.5), 0);
				
				world.add(make_shared<sphere>(position, position2, radius, objectMaterial));
				continue;
			}
			else if (randomMaterial < 0.85) // Metal
			{
				color3 albedo = randomColor(0, 0.51) * randomColor(0, 0.51);
				double fuzz = randomDouble(0, 0.501);
				objectMaterial = make_shared<metal>(albedo, fuzz);
			}
			else // Dielectric
			{
				objectMaterial = make_shared<dielectric>(randomDouble(1.5, 1.71));
			}

			world.add(make_shared<sphere>(position, radius, objectMaterial));
		}
	}

	world = objectlist(make_shared<bvhnode>(world));

	camera.render(world);

	std::cout.rdbuf(originalBuffer);
	return 0;
}