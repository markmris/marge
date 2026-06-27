#pragma once

#include "ray.h"

struct hitdata
{
    point3 point;
    vector3 normal;
    double t;
};

struct hittable
{
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double rayTmin, double rayTmax, hitdata& hd) const = 0;
};