#pragma once
#include <iostream>
#include <fstream>
#include "ray.h"
#include "texture.h"
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

	//Emissive
	virtual vec3 emitted(float u, float v, const vec3 &p)const;
private:

};

class lambertian :public Material
{
private:
	Texture*   _albedo;
public:
	//lambertian(const vec3& rAlbedo) : _albedo(rAlbedo) {};
	lambertian( Texture*  a);
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

//Emissive
class diffuseLight : public Material
{
public:
	diffuseLight(Texture* a);

	virtual bool scatter(const Ray& rayIn, const Hit_record& rec, vec3& attenuation, Ray& scattered) const override;

	virtual vec3 emitted(float u, float v, const vec3 &p)const;

private:
	Texture*	_emit;
};
