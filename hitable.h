#pragma once
#include <iostream>
#include "ray.h"
#include "aabb.h"

class Material;

struct Hit_record
{
	float t;
	vec3  p;
	vec3 normal;
	Material* matPtr;
};


class Hitable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const = 0;

	//add boundingbox for AABB algorithem
	virtual bool boundingBox(float t0, float t1, AABB& box)  const = 0;

private:

};


class BvhNode : public Hitable
{
	BvhNode();
	BvhNode(Hitable** l, int n, float time0, float time1);
	virtual bool hit(const Ray& r, float tmin, float tmax, Hit_record & rec) const override;
private:
	Hitable*	_left;
	Hitable*	_right;
	AABB		box;
};



int boxCompare(const void* a, const void* b);