#include "marge.h"
#include "objects.h"

void getSphereUV(const point3& point, double& u, double& v)
{
    auto theta = std::acos(-point.y);
    auto phi = std::atan2(-point.z, -point.x) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}

sphere::sphere(const point3& position, double radius, shared_ptr<::material> material) : position(position, vector3(0, 0, 0)), radius(std::fmax(0, radius)), material(material) {}
sphere::sphere(const point3& position1, const point3& position2, double radius, shared_ptr<::material> material) : position(position1, position2 - position1), radius(radius), material(material) {}

bool sphere::hit(const ray& r, interval rayt, hitdata& hd) const
{
    point3 currentPosition = position.at(r.time);
    vector3 oc = currentPosition - r.origin;
	auto a = r.direction.magnitudeSqr();
	auto b = dot(r.direction, oc);
	auto c = oc.magnitudeSqr() - radius * radius;
	auto discriminant = b * b - a * c;

    if (discriminant < 0.0)
        return false;
    
    auto sqrtd = std::sqrt(discriminant);
    auto root = (b - sqrtd) / a;

    if (!rayt.surrounds(root))
    {
        root = (b + sqrtd) / a;

        if (!rayt.surrounds(root))
            return false;
    }

    hd.t = root; // Closest point in the acceptable range that the ray hit
    hd.point = r.at(hd.t); // The world position of the hit
    vector3 outwardNormal = (hd.point - currentPosition) / radius;
    hd.setFaceNormal(r, outwardNormal);
    getSphereUV(outwardNormal, hd.horizontalCoord, hd.verticalCoord);
    hd.material = material;

    return true;
}