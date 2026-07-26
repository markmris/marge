#pragma once

#include "marge.h"

struct material;

struct hitdata
{
    // Where the ray was hit
    point3 point;
    double t;

    // The surface the ray hit
    bool frontFace;
    vector3 normal;

    shared_ptr<material> material;

    // Determines whether the ray hit the inside or the outside of the sphere.
    void setFaceNormal(const ray& r, const vector3& outwardNormal);
};

struct hittable
{
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval rayt, hitdata& hd) const = 0;
};