#include "marge.h"
#include "camera.h"
#include "hittable.h"
#include "objects.h"
#include "objectlists.h"
#include "material.h"
#include "commandline.h"
#include "bvh.h"
#include "texture.h"
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upward, Negative Y downward, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backward
*/

static void initializeEngine(int argc, char* argv[], camera& camera, int& globalObjectCount);
static void getTextures(std::vector<shared_ptr<imagetexture>>& images);

std::ofstream outFile("image.ppm");
std::streambuf* originalBuffer = std::cout.rdbuf();

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout.rdbuf(outFile.rdbuf());

	camera camera;
	int globalObjectCount = 20;

	initializeEngine(argc, argv, camera, globalObjectCount);

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

	std::vector<shared_ptr<imagetexture>> images;

	getTextures(images);

	shared_ptr<material> objectMaterial;
	shared_ptr<texture> perlinTexture = make_shared<perlintexture>(4);
	color3 albedo;

	for (int x = -globalObjectCount / 4; x < globalObjectCount / 4; x++)
	{
		for (int z = -globalObjectCount / 4; z < globalObjectCount / 4; z++)
		{
			double randomMaterial = randomDouble();
			double radius = randomDouble(0.15, 0.35);
			point3 position = point3(objectOrigin.x + x + randomDouble(-0.3, 0.3), radius, objectOrigin.z + z + randomDouble(-0.3, 0.3));
			point3 position2;

			if (randomMaterial < 0.8) // Diffuse
			{
				int sphereType;
				if (images.empty())
					sphereType = randomInt(1, 3);
				else
					sphereType = randomInt(1, 4);

				switch (sphereType)
				{
				case 1:
					albedo = randomColor() * randomColor();
					objectMaterial = make_shared<diffuse>(albedo);
					world.add(make_shared<sphere>(position, radius, objectMaterial));

					break;

				case 2:
					position2 = position + vector3(0, randomDouble(0, 0.5), 0);
					albedo = randomColor() * randomColor();
					objectMaterial = make_shared<diffuse>(albedo);
					world.add(make_shared<sphere>(position, position2, radius, objectMaterial));

					break;

				case 3:
					objectMaterial = make_shared<diffuse>(perlinTexture);
					world.add(make_shared<sphere>(position, radius, objectMaterial));

					break;

				case 4:
					int imageIndex = randomInt(0, static_cast<int>(images.size() - 1));
					world.add(make_shared<sphere>(position, radius, make_shared<diffuse>(images[imageIndex])));

					break;
				}
				
				continue;
			}
			else if (randomMaterial < 0.9) // Metal
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


static void initializeEngine(int argc, char* argv[], camera& camera, int& globalObjectCount)
{
	camera.cameraPoint = point3(13, 1.5, 3);
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 1080;
	camera.maxPixelSamples = 4;
	camera.maxDepth = 13;
	camera.fov = 90;
	camera.yaw = 0;
	camera.pitch = -45;
	camera.defocusAngle = 0.6;
	camera.focusDistance = 2.5;

	try
	{
		bool help = parseCommands(argc, argv, camera, globalObjectCount);

		if (help)
		{
			std::cout.rdbuf(originalBuffer);

			std::cout << helpmessage;

			std::exit(0);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';

		std::exit(0);
	}

	camera.initialize();
}

static void getTextures(std::vector<shared_ptr<imagetexture>>& images)
{
	if (std::filesystem::exists(textureDir))
	{
		const std::string supportedFiles[4] = { "jpg", "jpeg", "png", "tga" };

		for (const auto& img : std::filesystem::directory_iterator(textureDir))
		{
			std::string filename = img.path().filename().string();

			size_t index;
			for (const std::string& extension : supportedFiles)
			{
				index = filename.find(extension);

				if (index != std::string::npos)
					break;
			}

			if (index == std::string::npos)
			{
				std::cerr << "Filetype for file " << filename << " is not supported. Will not be rendered.";
				continue;
			}

			images.push_back(make_shared<imagetexture>(filename));
		}
	}
	else
	{
		std::clog << "No textures folder found. Image textures will not render." << '\n';
	}
}