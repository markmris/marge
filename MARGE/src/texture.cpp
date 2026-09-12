#include "texture.h"

solidcolor::solidcolor(const color3& albedo) : albedo(albedo) {}
solidcolor::solidcolor(const double red, const double green, const double blue) : solidcolor(color3(red, green, blue)) {}

color3 solidcolor::value(const double horizontalCoord, const double verticalCoord, const point3& point) const
{
	return albedo;
}

checkertexture::checkertexture(double scale, shared_ptr<texture> even, shared_ptr<texture> odd) : scale(scale), even(even), odd(odd) {}
checkertexture::checkertexture(double scale, const color3& c1, const color3& c2) : checkertexture(scale, make_shared<solidcolor>(c1), make_shared<solidcolor>(c2)) {}

color3 checkertexture::value(const double horizontalCoord, const double verticalCoord, const point3& point) const
{
	int xInt = int(std::floor(scale * point.x));
	int yInt = int(std::floor(scale * point.y));
	int zInt = int(std::floor(scale * point.z));

	bool isEven = (xInt + yInt + zInt) % 2 == 0;

	return isEven ? even->value(horizontalCoord, verticalCoord, point) : odd->value(horizontalCoord, verticalCoord, point);
}

imagetexture::imagetexture(const std::string fileName) : img(fileName) {}

color3 imagetexture::value(double horizontalCoord, double verticalCoord, const point3& point) const
{
	if (img.imageHeight <= 0) return color3(0, 1, 1);

	horizontalCoord = interval(0, 1).clamp(horizontalCoord);
	verticalCoord = 1.0 - interval(0, 1).clamp(verticalCoord);

	int x = int(horizontalCoord * img.imageWidth);
	int y = int(verticalCoord * img.imageHeight);
	const unsigned char* pixel = img.pixelData(x, y);

	double colorScale = 1.0 / 255.0;

	return color3(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
}

perlintexture::perlintexture(double scale) : scale(scale) {}

color3 perlintexture::value(double horizontalCoord, double verticalCoord, const point3& point) const
{
	return color3(1, 1, 1) * 0.5 * (1.0 + noise.noise(point * scale));
}