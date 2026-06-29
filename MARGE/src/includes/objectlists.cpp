#include <vector>
#include <memory>
#include "hittable.h"
#include "objectlists.h"

objectlist::objectlist() {}
objectlist::objectlist(shared_ptr<hittable> object) { add(object); }

void objectlist::add(shared_ptr<hittable> object)
{
    this->objects.push_back(object);
}

void objectlist::clear()
{
    this->objects.clear();
}

bool objectlist::hit(const ray& r, double rayTmin, double rayTmax, hitdata& hd) const
{
    hitdata hdTemp;
    bool hitAnything = false;
    auto closestObj = rayTmax;

    for (const auto& object : objects)
    {
        if (object->hit(r, rayTmin, closestObj, hdTemp))
        {
            hitAnything = true;
            closestObj = hdTemp.t;
            hd = hdTemp;
        }
    }

    return hitAnything;
}