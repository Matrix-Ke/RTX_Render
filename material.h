#pragma once
#include <iostream>
#include <fstream>
#include "ray.h"
#include "hitable.h"
#include "drand48.h"

//#define random(rAlbedo, b)   (rand()%(b - rAlbedo +1 ) +rAlbedo )
//#define drand48()	(float((rand()%100)) /100.0f)





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


class Material
{
public:
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const = 0;


private:

};

class lambertian :public Material
{
private:
	vec3   albedo;
public:
	lambertian(const vec3& rAlbedo) : albedo(rAlbedo) {};
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override
	{
		vec3 target = rec.normal + randomPointInUintsphere();
		scattered = Ray(rec.p, target);
		attenuation = albedo;
		return true;
	}

};


class metal : public Material
{
private:
	vec3	albedo;
	float   fuzz;
public:
	metal(const vec3& rAlbedo, const float f) : albedo(rAlbedo) 
	{
		if (f < 1)
			fuzz = f;
		else
			fuzz = 1.0f;
	};
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override
	{

		vec3	reflected = reflect(makeUnitVector(rayIn.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * randomPointInUintsphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};





