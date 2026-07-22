#include "includes/marge.h"
#include "includes/camera.h"
#include "includes/hittable.h"
#include "includes/objects.h"
#include "includes/objectlists.h"

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
	camera.maxPixelSamples = 2;
	camera.maxDepth = 10;

	// World Creation
	objectlist world;
	world.add(make_shared<sphere>(point3(-0.45, 0.3, 0.75), 0.3));
	world.add(make_shared<sphere>(point3(0.8, 0.2, 1.7), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, 1), 100));

	camera.render(world);

	return 0;
}