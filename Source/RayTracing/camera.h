#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ray.h"
#include "drand48.h"




class camera
{
private:
	vec3    _origin;
	vec3	_horizontal;
	vec3	_vertical;
	vec3	_lowerLeftCorner;
	vec3	_cameraX, _cameraY, _cameraDir;
	float   _cameraAperture;

	// add _startTime & _endTime
	float  _startTime;
	float  _endTime;

public:

	camera(const vec3& lookfrom, const vec3& lookat, const vec3 vUp, float vFov, float aspectRatio,
		float aperture, float focusDist, float sTime, float eTime);

	//   this u & v range from 0.0-1.0f;
	Ray getRay(float u, float v) const;

private:
	vec3 randomInUnitDisk() const;
};

