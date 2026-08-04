#pragma once

#include "hittable.h"

struct camera
{
public:
	point3 cameraPoint;

	double aspectRatio;
	int imageWidth;
	int maxPixelSamples;
	double pixelSamplesScale;
	int maxDepth;

	double fov;

	double pitch;
	double yaw;

	double defocusAngle;
	double focusDistance;

	void render(const hittable& world);
	vector3 getForward();
private:
	int imageHeight;

	double pitchRad;
	double yawRad;
	vector3 vup;
	vector3 forward;
	vector3 localRight;
	vector3 localUp;

	double viewportHeight, viewportWidth;
	vector3 viewportX, viewportY;
	vector3 pixelDeltaX, pixelDeltaY;
	point3 viewportUpperLeft, viewportOrigin;

	vector3 defocusDiskX;
	vector3 defocusDiskY;

	void initialize();
	color3 rayColor(const ray& r, const int& depth, const hittable& world) const;
	vector3 samplePixel() const;
	ray getRay(int j, int i) const;
	point3 defocusDiskSample() const;
};