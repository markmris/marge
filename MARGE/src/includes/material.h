#pragma once

#include "hittable.h"

struct material
{
	virtual ~material() = default;

	virtual bool scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const;
};

struct diffuse : public material
{
	color3 albedo;

	diffuse(const color3& albedo);
	bool scatter(const ray& rayIn, const hitdata& hd, color3& attenuation, ray& scattered) const override;
};