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
	vec3	lowerLeftCorner;

	vec3	cameraX, cameraY, cameraDir;
	float   cameraAperture;
public:

	camera(const vec3& lookfrom, const vec3& lookat, const vec3 vUp, const float vFov, float aspectRatio, float aperture, float focusDist )
	{
		cameraAperture = aperture;
		origin = lookfrom;

		float theta = vFov * M_PI / 180;
		float halfHeigh = tan(theta / 2);
		float halfWidth = aspectRatio * halfHeigh;
		
		cameraDir = lookfrom - lookat;
	    cameraX = cross(vUp, cameraDir);
	    cameraY = cross(cameraDir, cameraX);
		cameraDir.makeUnitVector();
		cameraX.makeUnitVector();
		cameraY.makeUnitVector();

		
		horizontal = 2 * halfWidth * cameraX;
		vertical = 2 * halfHeigh* cameraY;
		
		lowerLeftCorner = lookfrom - halfWidth * cameraX - halfHeigh * cameraY;



	}

	//   this u & v range from 0.0-1.0f;
	Ray getRay(float u, float v) const
	{
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}




};
