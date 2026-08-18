#pragma once

#include "marge.h"

struct texture
{
	virtual ~texture() = default;

	virtual color3 value(const double horizontalTexture, const double verticalTexture, const point3& point) const = 0;
};

struct solidcolor : public texture
{
private:
	color3 albedo;

public:
	solidcolor(const color3& albedo);
	solidcolor(const double red, const double green, const double blue);

	color3 value(const double horizontalTexture, const double verticalTexture, const point3& point) const override;
};

struct checkertexture : public texture
{
private:
	double scale;
	shared_ptr<texture> even;
	shared_ptr<texture> odd;

public:
	checkertexture(double scale, shared_ptr<texture> even, shared_ptr<texture> odd);
	checkertexture(double scale, const color3& c1, const color3& c2);

	color3 value(const double horizontalTexture, const double verticalTexture, const point3& point) const override;
};