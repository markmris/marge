#pragma once

#include <iostream>
#include <cmath>
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