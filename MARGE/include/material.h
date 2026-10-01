#pragma once

#include "hittable.h"
#include "texture.h"

struct material
{
	virtual ~material() = default;

	virtual bool scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const;
	virtual color3 emitted(double horizontalCoord, double verticalCoord, const point3& point) const;
};

struct diffuse : public material
{
	color3 albedo;
	shared_ptr<texture> surfaceTexture;

	diffuse(const color3& albedo);
	diffuse(shared_ptr<texture> surfaceTexture);
	bool scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const override;
};

struct metal : public material
{
	color3 albedo;
	double fuzz;

	metal(const color3& albedo, double fuzz);
	bool scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const override;
};

struct dielectric : public material
{
	double refractionIndex;
	
	dielectric(double refractionIndex);
	bool scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const override;
	static double reflectance(double cosine, double refractionIndex);
};

struct diffuselight : public material
{
	shared_ptr<texture> tex;

	diffuselight(shared_ptr<texture> tex);
	diffuselight(const color3& emit);

	color3 emitted(double horizontalCoord, double verticalCoord, const point3& point) const override;
};