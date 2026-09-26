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
static void quads();

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

	std::vector<shared_ptr<imagetexture>> images;

	getTextures(images);

	shared_ptr<material> objectMaterial;
	shared_ptr<texture> perlinTexture = make_shared<perlintexture>(4);
	color3 albedo;

	world = objectlist(make_shared<bvhnode>(world));

	camera.render(world);

	std::cout.rdbuf(originalBuffer);
	return 0;
}


static void initializeEngine(int argc, char* argv[], camera& camera, int& globalObjectCount)
{
	camera.cameraPoint = point3(0, 0, 0);
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 1080;
	camera.maxPixelSamples = 32;
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

static void renderScene(objectlist& world)
{
	auto wallmaterial = make_shared<diffuse>(color3(0.439, 0.439, 0.439));
	auto groundMaterial = make_shared<diffuse>(color3(0.8, 0.8, 0.8));

	world.add(make_shared<quadrilateral>(point3(-1, 3, 5), vector3(0, 0, 5), vector3(5, 0, 0), wallmaterial));
	world.add(make_shared<quadrilateral>(point3(-2.5, 3, 5), vector3(5, 0, 0), vector3(5, 0, 0), wallmaterial));
}