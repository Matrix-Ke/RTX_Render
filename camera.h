#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ray.h"
#include "drand48.h"




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

		lowerLeftCorner = lookfrom -  cameraX * halfWidth * focusDist - cameraY* halfHeigh * focusDist - cameraDir * focusDist ;
 
		horizontal = 2 * halfWidth *focusDist* cameraX;
		vertical = 2 * halfHeigh * focusDist* cameraY;
	}

	//   this u & v range from 0.0-1.0f;
	Ray getRay(float u, float v) const
	{
		vec3   unitVec = cameraAperture / 2 * this->random_in_unit_disk();
		vec3   offset = cameraX * unitVec.x() + cameraY * unitVec.y();
		vec3   startPnt = origin + offset;
		return Ray(startPnt, lowerLeftCorner + u * horizontal + v * vertical - startPnt);
	}

private:
	vec3 random_in_unit_disk() const 
	{
		vec3 p;
		do {
			p = 2.0*vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
		} while (dot(p, p) >= 1.0);
		return p;
	}
};

