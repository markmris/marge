#pragma once

#include "hittable.h"

void getSphereUV(const point3& point, double& u, double& v);

struct sphere : public hittable
{
    ray position;
    double radius;

    shared_ptr<::material> material;

    sphere(const point3& position, double radius, shared_ptr<::material> material);
    sphere(const point3& position1,const point3& position2, double radius, shared_ptr<::material> material);

    virtual bool hit(const ray& r, interval rayt, hitdata& hd) const override;
};