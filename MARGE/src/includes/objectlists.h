#pragma once

#include <vector>

#include "marge.h"

struct objectlist : public hittable
{
    std::vector<shared_ptr<hittable>> objects;

    objectlist();
    objectlist(shared_ptr<hittable> object);

    void add(shared_ptr<hittable> object);
    void clear();

    bool hit(const ray& r, interval rayt, hitdata& hd) const override;
};