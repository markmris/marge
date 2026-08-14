#include "ray.h"

ray::ray() : origin(point3(0, 0, 0)), direction(vector3(0, 0, 0)), time(0) {};
ray::ray(const point3& origin, const vector3& direction) : origin(origin), direction(direction), time(0) {};
ray::ray(const point3& origin, const vector3& direction, double time) : origin(origin), direction(direction), time(time) {}

point3 ray::at(const double& dist) const
{
    return this->origin + (this->direction * dist);
}