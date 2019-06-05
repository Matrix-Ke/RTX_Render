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
	AABB() {};
	AABB(const vec3& pointA, const vec3& pointB) : _min(pointA), _max(pointB) {};
	vec3 min() const { return _min; };
	vec3 max() const { return _max; };
	bool hit(const Ray&  r, float tmin, float tmax) const
	{
		for (int index = 0; index < 3; index++)
		{
			vec3 tempVec = r.direction();
			float invertDist = 1.0f / tempVec[index];
			float t0 = (_min[index] - tempVec[index]) * invertDist;
			float t1 = (_max[index] - tempVec[index]) * invertDist;
			if (invertDist < 0.0f)
			{
				std::swap(t0, t1);
			}

			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmin < tmax)
				return true;
		}
		return false;
	}
}; 



AABB surroundingBox(const AABB& box0, const	AABB& box1)
{
	vec3 small(fmin(box0.min().x(), box1.min().x()),
		fmin(box0.min().y(), box1.min().y()),
		fmin(box0.min().z(), box1.min().z()));
	vec3 big(fmax(box0.max().x(), box1.max().x()),
		fmax(box0.max().y(), box1.max().y()),
		fmax(box0.max().z(), box1.max().z()));
	return AABB(small, big);
}