#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() {};
	Ray(const vec3& sPnt, const vec3 & dir) : originPnt(sPnt), directionPnt(dir) {};
	vec3 origin() const { return originPnt; };
	vec3 direction() const { return directionPnt; };
	vec3 pointAtParameter(float t) const
	{
		return originPnt + t * (directionPnt - originPnt);
	}

private:
	vec3  originPnt;
	vec3  directionPnt;
};