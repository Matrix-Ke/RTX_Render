#pragma once

#include "hitable.h"


class sphere : public Hitable
{
public:
	sphere() {};
	sphere(const vec3& cen, const float r, Material* mPtr = nullptr) : center(cen), radius(r), matPtr(mPtr) {};
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override
	{
		vec3	oc = r.origin() - center;
		float a = dot(r.direction(), r.direction());
		float b = 2 * dot(oc, r.direction());
		float c = dot(oc, oc) - radius * radius;

		float discriminant = b * b - a * c * 4;
		if (discriminant >= 0)
		{
			float temp = (-b - sqrt(discriminant)) / (2 * a);
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.pointAtParameter(temp);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = matPtr;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / (2 * a);
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.pointAtParameter(temp);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = matPtr;
				return true;
			}
		}
		return false;
	}

private:
	vec3	center;
	float	radius;
	Material*  matPtr;
};



class MovingSphere : public Hitable
{
private:
	vec3    _centerPos1;
	vec3	_centerPos2;

	float  _startTime;
	float  _endTime;
	float  _radius;
	Material*  _matPtr;
public:
	MovingSphere() {};
	MovingSphere(const vec3& cen1, const vec3& cen2, float sTime, float eTime, float R, Material * mat) :
		_centerPos1(cen1), _centerPos2(cen2), _startTime(sTime), _endTime(eTime), _radius(R), _matPtr(mat) {};

	vec3  center(const float time) const
	{
		return _centerPos1 + (time - _startTime) / (_endTime - _startTime) * (_centerPos1 - _centerPos2);
	}

	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override
	{
		// 修改之前的center为一个时间相关的位置
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

};