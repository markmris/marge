#pragma once

#include "hittable.h"

struct camera
{
public:
	double aspectRatio;
	int imageWidth;
	int maxPixelSamples;
	double pixelSamplesScale;
	int maxDepth;

	void render(const hittable& world);
private:
	point3 cameraPoint;
	double focalLength;

	int imageHeight;

	double viewportHeight, viewportWidth;
	vector3 viewportX, viewportY;
	vector3 pixelDeltaX, pixelDeltaY;
	point3 viewportUpperLeft, viewportOrigin;

	void initialize();
	color3 rayColor(const ray& r, const int& depth, const hittable& world) const;
	vector3 samplePixel() const;
	ray getRay(int j, int i) const;
};