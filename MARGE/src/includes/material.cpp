#include "material.h"

bool material::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const
{
	return false;
}

diffuse::diffuse(const color3& albedo) : albedo(albedo) {}

bool diffuse::scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const override
{
	vector3 scatterDirection = hd.normal + randomNormalVector();

	if (scatterDirection.nearZero())
		scatterDirection = hd.normal;

	scattered = ray(hd.point, scatterDirection);
	attenuation = albedo;

	return true;
}