#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "ray.h"


class camera
{
private:
	vec3    origin;
	vec3	horizontal;
	vec3	vertical;
	vec3	lower_left_corner;

public:

	camera(const vec3& lookfrom, const vec3& lookat, const vec3 vUp, const float vFov, float aspect)
	{
		vec3 u, v, w;
		float theta = vFov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;

		w = makeUnitVector(lookfrom - lookat);
		u = makeUnitVector(cross(vUp, w));
		v = cross(w, u);

		//lower_left_corner = vec3(-half_width, -half_height, -1.0);
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width*u;
		vertical = 2 * half_height*v;
	}

	Ray getRay(float u, float v) const
	{
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}

};
