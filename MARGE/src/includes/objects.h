#pragma once

#include "hittable.h"

struct sphere : public hittable
{
    point3 position;
    double radius;

    sphere(const point3& position, double radius);

    virtual bool hit(const ray& r, interval rayt, hitdata& hd) const override;
};