#include "hittable.h"

void hitdata::setFaceNormal(const ray& r, const vector3& outwardNormal)
{
    this->frontFace = dot(r.direction, outwardNormal) < 0;
    this->normal = frontFace ? outwardNormal : -1 * outwardNormal;
}