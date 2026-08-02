#include "material.h"
#include <algorithm>

bool material::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const
{
	return false;
}


diffuse::diffuse(const color3& albedo) : albedo(albedo) {}
metal::metal(const color3& albedo, double fuzz) : albedo(albedo), fuzz(std::clamp(fuzz, 0.0, 1.0)) {}
dielectric::dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}


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

bool dielectric::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const
{
	attenuation = color3(1, 1, 1);
	double ri = hd.frontFace ? (1.0 / refractionIndex) : refractionIndex;

	vector3 normalDirection = normalized(rayIn.direction);
	vector3 refracted = refract(normalDirection, hd.normal, ri);

	double cosTheta = std::fmin(dot(-1 * normalDirection, hd.normal), 1.0);
	double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

	vector3 direction;

	if (ri * sinTheta > 1.0)
	{
		direction = reflect(normalDirection, hd.normal);
	}
	else
	{
		direction = refract(normalDirection, hd.normal, ri);
	}

	scattered = ray(hd.point, refracted);

	return true;
}