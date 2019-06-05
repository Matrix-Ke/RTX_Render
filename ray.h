#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() {};
	Ray(const vec3& sPnt, const vec3 & dir, float time = 0.0 ) : originPnt(sPnt), rayDirection(dir) , currentTime(time){};
	vec3 origin() const { return originPnt; };
	vec3 direction() const { return rayDirection; };
	vec3 pointAtParameter(float t) const
	{
		return originPnt + t * rayDirection;
	}
	float time() const { return currentTime; };

private:
	vec3  originPnt;
	vec3  rayDirection;
	float currentTime;
};