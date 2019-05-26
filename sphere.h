#pragma once

#include "hitable.h"


class sphere : public Hitable
{
public:
	sphere() {};
	sphere(const vec3& cen, const float r) : center(cen), radius(r) {};
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;

private:
	vec3	center;
	float	radius;
	Material*  matPtr;
};


bool sphere::hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const
{
	vec3	oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b -  a*c *4;
	if (discriminant >= 0)
	{
		float temp = (-b - sqrt(discriminant)) / (2 * a);
		if ( temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(temp);
			rec.normal = (rec.p - center) / radius;
			rec.matPtr = matPtr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2 *a);
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

