#include "ray.h"

ray::ray() : origin(point3(0, 0, 0)), direction(vector3(0, 0, 0)) {};
ray::ray(const point3& origin, const vector3& direction) : origin(origin), direction(direction) {};

point3 ray::at(const double& dist) const
{
    return this->origin + (this->direction * dist);
}