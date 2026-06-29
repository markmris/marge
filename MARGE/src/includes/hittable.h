#pragma once

#include "ray.h"

struct hitdata
{
    // Where the ray was hit
    point3 point;
    double t;

    // The surface the ray hit
    bool frontFace;
    vector3 normal;

    // Determines whether the ray hit the inside or the outside of the sphere.
    void setFaceNormal(const ray& r, const vector3& outwardNormal)
    {
        frontFace = dot(r.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -1 * outwardNormal;
    }
};

struct hittable
{
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double rayTmin, double rayTmax, hitdata& hd) const = 0;
};