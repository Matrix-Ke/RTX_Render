#pragma once
#include "ray.h"


class camera
{
private:
	vec3  origin;
	vec3	horizontal;
	vec3	vertical;
	vec3	lower_left_corner;


public:
	camera(const vec3& originPnt = vec3(0.0, 0.0, 0.0), const vec3& startPnt = vec3(-2.0, -1.0, -1.0),
		   const vec3& widthDir = vec3(4.0, 0.0, 0.0),const vec3& legnthDir = vec3(0.0, 2.0, 0.0) ):
		origin(originPnt), horizontal(widthDir), vertical(legnthDir), lower_left_corner(startPnt)
	{
	}

	Ray getRay(float u, float v) const
	{
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
	~camera();

private:

};
