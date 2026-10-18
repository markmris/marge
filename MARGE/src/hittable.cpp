#include "hittable.h"

void hitdata::setFaceNormal(const ray& r, const vector3& outwardNormal)
{
    this->frontFace = dot(r.direction, outwardNormal) < 0;
    this->normal = frontFace ? outwardNormal : -1 * outwardNormal;
}

translate::translate(vector3& offset, shared_ptr<hittable> object) : offset(offset), object(object) {}

bool translate::hit(const ray& r, interval rayt, hitdata& hd) const
{
    ray offsetRay(r.origin - offset, r.direction, r.time);

    if (!object->hit(offsetRay, rayt, hd))
        return false;
    
    hd.point = hd.point + offset;

    return true;
}

boundingbox translate::getBoundingBox() const { return bbox; }