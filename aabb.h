#pragma once
#include <algorithm>
#include "Vec3.h"
#include "ray.h"

class AABB
{
private:
	vec3	_min;
	vec3	_max;
public:
	AABB();
	AABB(const vec3& pointA, const vec3& pointB);
	vec3 min() const ;
	vec3 max() const ;
	bool hit(const Ray&  r, float tmin, float tmax) const;
}; 


AABB surroundingBox(const AABB& box0, const	AABB& box1);