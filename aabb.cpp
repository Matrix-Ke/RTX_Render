#include "aabb.h"

AABB::AABB()
{
}

AABB::AABB(const vec3 & pointA, const vec3 & pointB): _min(pointA), _max(pointB) 
{
}

vec3 AABB::min() const
{
	return _min;
}

vec3 AABB::max() const
{
	{ return _max; }
}

bool AABB::hit(const Ray & r, float tmin, float tmax) const
{
	vec3 tempVec = r.direction();
	vec3 origin = r.origin();
	for (int index = 0; index < 3; index++)
	{	
		float invertDist = 1.0f / tempVec[index];
		float t0 = (_min[index] - tempVec[index] - origin[index]) * invertDist;
		float t1 = (_max[index] - tempVec[index] - origin[index]) * invertDist;
		if (invertDist < 0.0f)
		{
			std::swap(t0, t1);
		}

		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;
		if (tmax <= tmin)
			return false;
	}
	return true;
}


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