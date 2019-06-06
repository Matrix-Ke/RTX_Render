#pragma once
#include <iostream>
#include <fstream>
#include "ray.h"
#include "hitable.h"
#include "drand48.h"
//#define random(rAlbedo, b)   (rand()%(b - rAlbedo +1 ) +rAlbedo )
//#define drand48()	(float((rand()%100)) /100.0f)


vec3   reflect(const vec3& v, const vec3&n);

vec3 randomPointInUintsphere();


class Material
{
public:
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const = 0;
private:

};

class lambertian :public Material
{
private:
	vec3   _albedo;
public:
	lambertian(const vec3& rAlbedo) : _albedo(rAlbedo) {};
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override;

};


class metal : public Material
{
private:
	vec3	_albedo;
	float   fuzz;
public:
	metal(const vec3& rAlbedo, const float f);
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override;
};




//this code for dielectrics material
// 反射系数的求解是是一个非常复杂的过程，Christophe Schlick这个人提供一个逼近公式，
// 这个公式被称为“ChristopheSchlick’s Approximation”。Wiki链接：
// https://en.wikipedia.org/wiki/Schlick%27s_approximation

float schlick(float cosine, float ref_idx);


bool refract(const vec3& rayIn, const vec3& normal, float rayRatio, vec3& refracted);


class dielectric :public Material
{
private:
	float refractIndex;
	public:
	dielectric(float refIdx = 1.0f);
	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override;
};


