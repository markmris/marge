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

const double infinity;
const double pi;

inline double degAsRad(double degrees);
inline double randomDouble();
inline double randomDouble(double min, double max);