#include "bvh.h"

bvhnode::bvhnode(objectlist list) : bvhnode(list.objects, 0, list.objects.size()) {};

bvhnode::bvhnode(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end)
{
	bbox = boundingbox::empty;

	for (size_t objectIndex = start; objectIndex < end; objectIndex++)
	{
		bbox = boundingbox(bbox, objects[objectIndex]->getBoundingBox());
	}

	int axis = bbox.getLongestAxis();

	auto comparator = (axis == 0) ? compareBoxX :
		(axis == 1) ? compareBoxY : compareBoxZ;

	size_t objectSpan = end - start;

	if (objectSpan == 1)
	{
		left = right = objects[start];
	}
	else if (objectSpan == 2)
	{
		left = objects[start];
		right = objects[start + 1];
	}
	else
	{
		std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

		auto middle = start + objectSpan / 2;
		left = make_shared<bvhnode>(objects, start, middle);
		right = make_shared<bvhnode>(objects, middle, end);
	}
}

bool bvhnode::boxCompare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b, int axisIndex)
{
	interval axisIntervalA = a->getBoundingBox().axisInterval(axisIndex);
	interval axisIntervalB = b->getBoundingBox().axisInterval(axisIndex);

	return axisIntervalA.min < axisIntervalB.min;
}

bool bvhnode::compareBoxX(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) { return boxCompare(a, b, 0); }
bool bvhnode::compareBoxY(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) { return boxCompare(a, b, 1); }
bool bvhnode::compareBoxZ(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) { return boxCompare(a, b, 2); }

bool bvhnode::hit(const ray& r, interval rayT, hitdata& hd) const
{
	if (!bbox.hit(r, rayT)) return false;

	bool leftHit = left->hit(r, rayT, hd);
	bool rightHit = right->hit(r, interval(rayT.min, leftHit ? hd.t : rayT.max), hd);

	return leftHit || rightHit;
}

boundingbox bvhnode::getBoundingBox() const { return bbox; }