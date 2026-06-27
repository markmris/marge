#include <cmath>
#include "objects.h"

sphere::sphere(const point3& position, double radius) : position(position), radius(std::fmax(0, radius)) {}

bool sphere::hit(const ray& r, double rayTmin, double rayTmax, hitdata& hd) const
{
    vector3 oc = position - r.origin;
	auto a = r.direction.magnitudeSqr();
	auto b = dot(r.direction, oc);
	auto c = oc.magnitudeSqr() - radius * radius;
	auto discriminant = b * b - a * c;

    if (discriminant < 0.0)
        return false;
    
    auto sqrtd = std::sqrt(discriminant);
    auto root = (b - sqrtd) / a;

    if (root <= rayTmin || rayTmax <= root)
    {
        root = (b + sqrtd) / a;

        if (root <= rayTmin || rayTmax <= root)
            return false;
    }

    hd.t = root;
    hd.point = r.at(hd.t);
    hd.normal = (hd.point - position) / radius;

    return true;
}