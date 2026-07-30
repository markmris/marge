#include "material.h"

bool material::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const
{
	return false;
}

diffuse::diffuse(const color3& albedo) : albedo(albedo) {}
metal::metal(const color3& albedo, double fuzz) : albedo(albedo), fuzz(std::clamp(fuzz, 0.0, 1.0)) {}

bool diffuse::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const
{
	vector3 scatterDirection = hd.normal + randomNormalVector();

	if (scatterDirection.nearZero())
		scatterDirection = hd.normal;

	scattered = ray(hd.point, scatterDirection);
	attenuation = albedo;

	return true;
}

bool metal::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const
{
	vector3 reflected = reflect(rayIn.direction, hd.normal);
	reflected = normalized(reflected) + (fuzz * randomNormalVector());
	scattered = ray(hd.point, reflected);
	attenuation = albedo;

	return dot(scattered.direction, hd.normal);
}