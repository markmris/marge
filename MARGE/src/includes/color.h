#pragma once

#include "vector3.h"

using color3 = vector3;

void writeColor(std::ostream& out, const color3 &color);
double linearToGamma(double linearComponent);
color3 randomColor();
color3 randomColor(double min, double max);