#include "texture.h"

solidcolor::solidcolor(const color3& albedo) : albedo(albedo) {}
solidcolor::solidcolor(const double red, const double green, const double blue) : solidcolor(color3(red, green, blue)) {}