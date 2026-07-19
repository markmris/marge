#pragma once

#include <iostream>
#include <cmath>
#include <memory>
#include <limits>
#include <random>

#include "vector3.h"
#include "ray.h"
#include "color.h"
#include "interval.h"

using std::make_shared;
using std::shared_ptr;

extern const double infinity;
extern const double pi;

double degAsRad(double degrees);
double randomDouble();
double randomDouble(double min, double max);