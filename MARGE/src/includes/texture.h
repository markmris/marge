#pragma once

#include "marge.h"

struct texture
{
	virtual ~texture() = default;
};

class solidcolor : public texture
{
	color3 albedo;

	solidcolor(const color3& albedo);
	solidcolor(const double red, const double green, const double blue);
};