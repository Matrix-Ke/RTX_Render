#pragma once
#include <iostream>
#include <fstream>
#include "ray.h"
#include "hitable.h"

#define random(a, b)   (rand()%(b - a +1 ) +a )
#define randomNum	(float((rand()%100)) /100.0f)





vec3   reflect(const vec3& v, const vec3&n)
{
	return v - 2 * dot(v, n) * n;
}

vec3 randomPointInUintsphere()
{
	vec3  point;
	do
	{
		point = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (dot(point, point) >= 1.0);
	return point;
}


class material
{
public:
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const = 0;


private:

};

class lambertian :public material
{
private:
	vec3   albedo;
public:
	lambertian(const vec3& a) : albedo(a) {};
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override
	{
		vec3 targte = rec.p + rec.normal + 
	}

private:

};

