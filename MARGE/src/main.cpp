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
#include <filesystem>
#include <cstdlib>

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upward, Negative Y downward, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backward
*/

static void initializeEngine(const int argc, char* argv[], camera& camera, int& globalObjectCount);
static void getTextures(std::vector<shared_ptr<imagetexture>>& images);
static void renderScene(objectlist& world);

std::ofstream outFile("image.ppm");
std::streambuf* originalBuffer = std::cout.rdbuf();

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout.rdbuf(outFile.rdbuf());

	camera cam;
	int globalObjectCount = 20;

	initializeEngine(argc, argv, cam, globalObjectCount);

	// World Creation
	objectlist world;

	renderScene(world);

	world = objectlist(make_shared<bvhnode>(world));

	cam.render(world);

	std::cout.rdbuf(originalBuffer);
	return 0;
}


static void initializeEngine(const int argc, char* argv[], camera& cam, int& globalObjectCount)
{
	cam.cameraPoint = point3(0.5, 1, 0);
	cam.aspectRatio = 16.0 / 9.0;
	cam.imageWidth = 1080;
	cam.maxPixelSamples = 32;
	cam.maxDepth = 13;
	cam.fov = 90;
	cam.yaw = 0;
	cam.pitch = 0;
	cam.defocusAngle = 0.6;
	cam.focusDistance = 2.5;

	try
	{
		bool help = parseCommands(argc, argv, cam, globalObjectCount);

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

	cam.initialize();
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
	auto wallmaterial = make_shared<diffuse>(color3(0.239, 0.239, 0.239));
	auto groundMaterial = make_shared<diffuse>(color3(0.8, 0.8, 0.8));

	world.add(make_shared<quadrilateral>(point3(-2.5, -0.1, -0.1), vector3(0, 0, 5), vector3(0, 5, 0), wallmaterial));
	world.add(make_shared<quadrilateral>(point3(-2.5, -0.1, 4.9), vector3(5, 0, 0), vector3(0, 5, 0), wallmaterial));
	world.add(make_shared<quadrilateral>(point3(2.5, -0.1, -0.1), vector3(0, 0, 5), vector3(0, 5, 0), wallmaterial));
	// world.add(make_shared<quadrilateral>(point3(-2.5, -0.1, -0.1), vector3(5, 0, 0), vector3(0, 5, 0), wallmaterial));
	world.add(make_shared<quadrilateral>(point3(-2.5, 4.9, -0.1), vector3(5, 0, 0), vector3(0, 0, 5), groundMaterial));
	world.add(make_shared<quadrilateral>(point3(-2.5, -0.1, -0.1), vector3(5, 0, 0), vector3(0, 0, 5), groundMaterial));

	std::vector<shared_ptr<imagetexture>> images;
	getTextures(images);

	int maxSurfaceTypes = 3;
	if (!images.empty())
		maxSurfaceTypes = 4;

	shared_ptr<material> objectMaterial;
	shared_ptr<texture> perlinTexture = make_shared<perlintexture>(4);
	color3 albedo;

	vector3 objectPosition;
	double radius;
	int imageIndex;

	for (int i = 0; i < 20; i++)
	{
		objectPosition = vector3(randomDouble(-2.3, 2.3), randomDouble(0.5, 4.8), randomDouble(1.5, 4.8));
		radius = randomDouble(0.1, 0.5);
		
		switch(randomInt(1, maxSurfaceTypes))
		{
			case 1:
				albedo = randomColor() * randomColor();
				objectMaterial = make_shared<diffuse>(albedo);
				break;
			
			case 2:
				albedo = randomColor() * randomColor();
				objectMaterial = make_shared<metal>(albedo, randomDouble(0, 1));
				break;
			
			case 3:
				objectMaterial = make_shared<dielectric>(randomDouble(1.5, 1.7));
				break;
			
			case 4:
				imageIndex = randomInt(0, static_cast<int>(images.size() - 1));
				break;
		}

		world.add(make_shared<sphere>(objectPosition, radius, objectMaterial));
	}	
}