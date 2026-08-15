#include "bvh.h"

bvhnode::bvhnode(objectlist list) : bvhnode(list.objects, 0, list.objects.size()) {};

bool bvhnode::boxCompare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b, int axisIndex)
{
	interval axisIntervalA = a->getBoundingBox().axisInterval(axisIndex);
	interval axisIntervalB = b->getBoundingBox().axisInterval(axisIndex);

	return axisIntervalA.min < axisIntervalB.min;
}

bool bvhnode::hit(const ray& r, interval rayT, hitdata& hd) const
{
	if (!bbox.hit(r, rayT)) return false;

	bool leftHit = left->hit(r, rayT, hd);
	bool rightHit = right->hit(r, rayT, hd);

	return leftHit || rightHit;
}

boundingbox bvhnode::getBoundingBox() const { return bbox; }