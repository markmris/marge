#pragma once

#include "vector3.h"

using point3 = vector3;

struct ray
{
    point3 origin;
    vector3 direction;
    double time;

    ray();
    ray(const point3& origin, const vector3& direction);
    ray(const point3& origin, const vector3& direction, double time);

    point3 at(const double& dist) const;
};