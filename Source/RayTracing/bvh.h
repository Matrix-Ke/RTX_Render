#pragma once
#include "hitable.h"

class BvhNode : public Hitable
{
public:
	BvhNode();
	BvhNode(Hitable** l, int n, float time0, float time1);
	virtual bool hit(const Ray& r, float tmin, float tmax, Hit_record & rec) const override;
	virtual bool boundingBox(float t0, float t1, AABB& box)  const override;
private:
	Hitable*	_left;
	Hitable*	_right;
	AABB		_box;
};



int boxXCompare(const void* a, const void* b);

int boxYCompare(const void* a, const void* b);

int boxZCompare(const void* a, const void* b);
