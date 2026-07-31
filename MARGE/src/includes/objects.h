#pragma once

#include "hittable.h"

struct sphere : public hittable
{
    point3 position;
    double radius;

    shared_ptr<::material> material;

    sphere(const point3& position, double radius, shared_ptr<::material> material);

    virtual bool hit(const ray& r, interval rayt, hitdata& hd) const override;
};