#pragma once

#include <vector>
#include <memory>
#include "hittable.h"

using std::make_shared;
using std::shared_ptr;

struct objectlist : public hittable
{
    std::vector<shared_ptr<hittable>> objects;

    objectlist();
    objectlist(shared_ptr<hittable> object);

    void add(shared_ptr<hittable> object);
    void clear();

    bool hit(const ray& r, double rayTmin, double rayTmax, hitdata& hd) const override;
};