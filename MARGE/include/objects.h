#pragma once

#include "hittable.h"
#include "objectlists.h"

struct sphere : public hittable
{
private:
    boundingbox bbox;

public:
    ray position;
    double radius;

    shared_ptr<::material> mat;

    sphere(const point3& staticPosition, double radius, shared_ptr<::material> mat);
    sphere(const point3& position1,const point3& position2, double radius, shared_ptr<::material> mat);

    static void getSphereUV(const point3& point, double& horizontalTexture, double& verticalTexture);

    bool hit(const ray& r, interval rayt, hitdata& hd) const override;
    boundingbox getBoundingBox() const override;
};

struct quadrilateral : public hittable
{
private:
    boundingbox bbox;
    vector3 normal;
    vector3 scaledNormal;
    double planeConst;

public:
    point3 cornerOrigin;
    vector3 horizontal, vertical;
    shared_ptr<::material> mat;

    quadrilateral(const point3& cornerOrigin, const vector3& horizontal, const vector3& vertical, shared_ptr<::material> mat);

    virtual void setBoundingBox();
    virtual bool isInterior(double a, double b, hitdata& hd) const;
    bool hit(const ray& r, interval rayt, hitdata& hd) const override;
    boundingbox getBoundingBox() const override;
};

inline shared_ptr<objectlist> box(const point3& a, const point3& b, shared_ptr<material> mat)
{
    auto sides = make_shared<objectlist>();

    point3 min(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.x, b.x));
    point3 max(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));

    vector3 dx(max.x - min.x, 0, 0);
    vector3 dy(0, max.y - min.y, 0);
    vector3 dz(0, 0, max.z - min.z);

    sides->add(make_shared<quadrilateral>(point3(min.x, min.y, min.z), dx, dy, mat));
    sides->add(make_shared<quadrilateral>(point3(max.x, min.y, max.z), -1 * dz, dy, mat));
    sides->add(make_shared<quadrilateral>(point3(max.x, min.y, min.z), -1 * dx, dy, mat));
    sides->add(make_shared<quadrilateral>(point3(min.x, min.y, min.z), dz, dy, mat));
    sides->add(make_shared<quadrilateral>(point3(min.x, max.y, max.z), dx, -1 * dz, mat));
    sides->add(make_shared<quadrilateral>(point3(min.x, min.y, min.z), dx, dz, mat));

    return sides;
}