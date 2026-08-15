#include "bvh.h"

bvhnode::bvhnode(objectlist list) : bvhnode(list.objects, 0, list.objects.size()) {};

bvhnode::bvhnode(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end)
{
	int axis = randomInt(0, 2);

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
		left = make_shared<bvhnode>(objects, start, end);
		right = make_shared<bvhnode>(objects, middle, end);
	}

	bbox = boundingbox(left->getBoundingBox(), right->getBoundingBox());
}

bool bvhnode::boxCompare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b, int axisIndex)
{
	interval axisIntervalA = a->getBoundingBox().axisInterval(axisIndex);
	interval axisIntervalB = b->getBoundingBox().axisInterval(axisIndex);

	return axisIntervalA.min < axisIntervalB.min;
}

bool bvhnode::compareBoxX(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) { boxCompare(a, b, 0); }
bool bvhnode::compareBoxY(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) { boxCompare(a, b, 1); }
bool bvhnode::compareBoxZ(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) { boxCompare(a, b, 2); }

bool bvhnode::hit(const ray& r, interval rayT, hitdata& hd) const
{
	if (!bbox.hit(r, rayT)) return false;

	bool leftHit = left->hit(r, rayT, hd);
	bool rightHit = right->hit(r, rayT, hd);

	return leftHit || rightHit;
}

boundingbox bvhnode::getBoundingBox() const { return bbox; }