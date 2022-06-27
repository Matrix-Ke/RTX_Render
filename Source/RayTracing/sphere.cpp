#include "sphere.h"

sphere::sphere(const vec3 & cen, const float r, Material * mPtr) : _center(cen), _radius(r), _matPtr(mPtr)
{
}

bool sphere::hit(const Ray & r, float t_min, float t_max, Hit_record & rec) const
{
	vec3	oc = r.origin() - _center;
	float a = dot(r.direction(), r.direction());
	float b = 2 * dot(oc, r.direction());
	float c = dot(oc, oc) - _radius * _radius;

	float discriminant = b * b - a * c * 4;
	if (discriminant >= 0)
	{
		float temp = (-b - sqrt(discriminant)) / (2 * a);
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(temp);
			getSphereUV((rec.p - _center) / _radius, rec.u, rec.v);
			rec.normal = (rec.p - _center) / _radius;
			rec.matPtr = _matPtr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2 * a);
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(temp);
			getSphereUV((rec.p - _center) / _radius, rec.u, rec.v);
			rec.normal = (rec.p - _center) / _radius;
			rec.matPtr = _matPtr;
			return true;
		}
	}
	return false;
}

bool sphere::boundingBox(float t0, float t1, AABB & box) const
{
	box = AABB(_center - vec3(_radius, _radius, _radius), _center + vec3(_radius, _radius, _radius));
	return true;
}

MovingSphere::MovingSphere()
{
}

MovingSphere::MovingSphere(const vec3 & cen1, const vec3 & cen2, float sTime, float eTime, float R, Material * mat) :
	_centerPos1(cen1), _centerPos2(cen2), _startTime(sTime), _endTime(eTime), _radius(R), _matPtr(mat)
{
};

vec3 MovingSphere::center(const float time) const
{
	return _centerPos1 + (time - _startTime) / (_endTime - _startTime) * (_centerPos1 - _centerPos2);
}

bool MovingSphere::hit(const Ray & r, float t_min, float t_max, Hit_record & rec) const
{
	// 
	vec3 oc = r.origin() - center(r.time());
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - _radius * _radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / _radius;
			rec.matPtr = _matPtr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / _radius;
			rec.matPtr = _matPtr;
			return true;
		}
	}
	return false;
}

bool MovingSphere::boundingBox(float t0, float t1, AABB & box) const
{
	AABB box0(center(t0) - vec3(_radius, _radius, _radius), center(t0) + vec3(_radius, _radius, _radius));
	AABB box1(center(t1) - vec3(_radius, _radius, _radius), center(t1) + vec3(_radius, _radius, _radius));
	box = surrounding_box(box0, box1);
	return true;
}

AABB MovingSphere::surrounding_box(AABB & box0, AABB & box1) const
{
	vec3 small(fmin(box0.min().x(), box1.min().x()),
		fmin(box0.min().y(), box1.min().y()),
		fmin(box0.min().z(), box1.min().z()));
	vec3 big(fmax(box0.max().x(), box1.max().x()),
		fmax(box0.max().y(), box1.max().y()),
		fmax(box0.max().z(), box1.max().z()));
	return AABB(small, big);
}
