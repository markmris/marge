#pragma once

#include "hittable.h"

struct material
{
	virtual ~material() = default;

	virtual bool scatter(const ray& rayIn, const hitdata& hd, const color3& attenuation, ray& scattered) const;
};