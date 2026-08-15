#pragma once

#include "boundingbox.h"
#include "hittable.h"
#include "objectlists.h"

struct bvhnode : public hittable
{
	bvhnode(objectlist list);
	bvhnode(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end);

	bool hit(const ray& r, interval rayT, hitdata& hd) const override;

	boundingbox getBoundingBox() const override;

private:
	shared_ptr<hittable> left;
	shared_ptr<hittable> right;
	boundingbox bbox;
};