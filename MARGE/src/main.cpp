#include "includes/marge.h"
#include "includes/camera.h"
#include "includes/hittable.h"
#include "includes/objects.h"
#include "includes/objectlists.h"
#include "includes/material.h"

/*
	X: Positive X to the right, Negative to the left
	Y: Positive Y upward, Negative Y downward, except viewport coordinates are inverted
	Z: Positive Z forward, Negative Z backward
*/

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	camera camera;
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 1080;
	camera.maxPixelSamples = 100;
	camera.maxDepth = 10;

	// World Creation
	objectlist world;

	auto groundMaterial = make_shared<diffuse>(color3(0.478, 0.859, 0.031));
	auto diffuseSphereMaterial = make_shared<diffuse>(color3(0, 0.733, 1));
	auto metalSphereMaterial = make_shared<metal>(color3(0.8, 0.8, 0.8));

	world.add(make_shared<sphere>(point3(0.8, 0, 1.2), 0.5, diffuseSphereMaterial));
	world.add(make_shared<sphere>(point3(-0.6, 0.15, 1.2), 0.65, metalSphereMaterial));
	world.add(make_shared<sphere>(point3(0, -100.5, 1), 100, groundMaterial));

	camera.render(world);

	return 0;
}