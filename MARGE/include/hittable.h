#pragma once

#include "marge.h"
#include "boundingbox.h"

struct material;

struct hitdata
{
    // Where the ray was hit
    point3 point;
    double t;

    // The surface the ray hit
    bool frontFace;
    vector3 normal;
    double horizontalTexture;
    double verticalTexture;

    shared_ptr<::material> material;

    double horizontalCoord;
    double verticalCoord;

    // Determines whether the ray hit the inside or the outside of the sphere.
    void setFaceNormal(const ray& r, const vector3& outwardNormal);
};

struct hittable
{
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval rayt, hitdata& hd) const = 0;
    virtual boundingbox getBoundingBox() const = 0;
};

struct translate : public hittable
{
    vector3 offset;
    shared_ptr<hittable> object;
    boundingbox bbox;

    translate(vector3& offset, shared_ptr<hittable> object);
    bool hit(const ray& r, interval rayt, hitdata& hd) const override;
    boundingbox getBoundingBox() const override;
};