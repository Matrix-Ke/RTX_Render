#include "ray.h"

Ray::Ray(const vec3 & sPnt, const vec3 & dir, float time) : originPnt(sPnt), rayDirection(dir), currentTime(time)
{
}

vec3 Ray::origin() const
{
	return originPnt;
}

vec3 Ray::direction() const
{
	return rayDirection;
}

vec3 Ray::pointAtParameter(float t) const
{
	return originPnt + t * rayDirection;
}

float Ray::time() const
{
	return currentTime;
}
