#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() {};
	Ray(const vec3& sPnt, const vec3 & dir, float time = 0.0 );
	vec3 origin() const;
	vec3 direction() const ;
	vec3 pointAtParameter(float t) const;
	float time() const ;

private:
	vec3  originPnt;
	vec3  rayDirection;
	float currentTime;
};