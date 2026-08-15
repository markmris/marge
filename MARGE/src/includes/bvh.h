#pragma once

#include "boundingbox.h"
#include "hittable.h"
#include "objectlists.h"

struct bvhnode : public hittable
{
	bvhnode(objectlist list);
	bvhnode(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end);

	static bool boxCompare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b, int axisIndex);
	static bool compareBoxX(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b);
	static bool compareBoxY(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b);
	static bool compareBoxZ(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b);

	bool hit(const ray& r, interval rayT, hitdata& hd) const override;
	boundingbox getBoundingBox() const override;

private:
	shared_ptr<hittable> left;
	shared_ptr<hittable> right;
	boundingbox bbox;
};