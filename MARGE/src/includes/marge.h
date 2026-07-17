#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <limits>

#include "vector3.h"
#include "ray.h"
#include "color.h"
#include "interval.h"

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degAsRad(double degrees)
{
    return (degrees * pi) / 180;
}

// Return a random real number in [0, 1)
inline double randomDouble()
{
    return std::rand() / (RAND_MAX + 1.0);
}

// Return a random real number in [min, max)
inline double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}