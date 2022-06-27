#include "camera.h"

camera::camera(const vec3 & lookfrom, const vec3 & lookat, const vec3 vUp, float vFov, float aspectRatio, float aperture, float focusDist, float sTime, float eTime)
{
		_startTime = sTime;
		_endTime = eTime;
		_cameraAperture = aperture;
		_origin = lookfrom;

		float theta = vFov * M_PI / 180;
		float halfHeigh = tan(theta / 2);
		float halfWidth = aspectRatio * halfHeigh;

		_cameraDir = lookfrom - lookat;
		_cameraX = cross(vUp, _cameraDir);
		_cameraY = cross(_cameraDir, _cameraX);
		_cameraDir.makeUnitVector();
		_cameraX.makeUnitVector();
		_cameraY.makeUnitVector();

		_lowerLeftCorner = lookfrom - _cameraX * halfWidth * focusDist - _cameraY * halfHeigh * focusDist - _cameraDir * focusDist;

		_horizontal = 2 * halfWidth *focusDist* _cameraX;
		_vertical = 2 * halfHeigh * focusDist* _cameraY;
}

Ray camera::getRay(float u, float v) const
{
	vec3   unitVec = _cameraAperture / 2 * this->randomInUnitDisk();
	vec3   offset = _cameraX * unitVec.x() + _cameraY * unitVec.y();
	vec3   startPnt = _origin + offset;
	//add timeStamps 
	float	time = _startTime + drand48() * (_endTime - _startTime);
	return Ray(startPnt, _lowerLeftCorner + u * _horizontal + v * _vertical - startPnt, time);
}

vec3 camera::randomInUnitDisk() const
{
	vec3 p;
	do {
		p = 2.0*vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}
