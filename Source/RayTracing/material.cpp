#include "material.h"

vec3 reflect(const vec3 & v, const vec3 & n)
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

float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

bool refract(const vec3 & rayIn, const vec3 & normal, float rayRatio, vec3 & refracted)
{
	vec3 unitRay = makeUnitVector(rayIn);
	float dt = dot(unitRay, normal);
	//  discrimmant is equal to (1- sin2平方)的平方；
	float discrimant = 1.0 - rayRatio * rayRatio *(1 - dt * dt);
	if (discrimant > 0)
	{
		//折射光线
		refracted = rayRatio * (unitRay - normal * dt) - normal * sqrt(discrimant);
		return true;
	}
	else
		return false;
}

vec3 Material::emitted(float u, float v, const vec3 & p) const
{
	return vec3(0, 0, 0);
};

lambertian::lambertian(Texture*   a):_albedo(a)
{
}

bool lambertian::scatter(const Ray & rayIn, const Hit_record & rec, vec3 & attenuation, Ray & scattered) const
{
	vec3 target = rec.normal + randomPointInUintsphere();
	scattered = Ray(rec.p, target);
	attenuation = _albedo->value(rec.u, rec.v, rec.p);
	return true;
}

metal::metal(const vec3 & rAlbedo, const float f) : _albedo(rAlbedo)
{
	if (f < 1)
		fuzz = f;
	else
		fuzz = 1.0f;
	std::cout << fuzz << std::endl;
}

bool metal::scatter(const Ray & rayIn, const Hit_record & rec, vec3 & attenuation, Ray & scattered) const
{

	vec3	reflected = reflect(makeUnitVector(rayIn.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + fuzz * randomPointInUintsphere());
	attenuation = _albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(float refIdx) :refractIndex(refIdx) {}
bool dielectric::scatter(const Ray & rayIn, const Hit_record & rec, vec3 & attenuation, Ray & scattered) const
{
	vec3	outWardNormal;
	vec3	reflected = reflect(rayIn.direction(), rec.normal);
	float	rayRatio;
	attenuation = vec3(1.0, 1.0, 1.0);
	vec3	refracted;
	float reflectProb;
	float cosine;
	if (dot(rayIn.direction(), rec.normal) > 0)
	{
		outWardNormal = -rec.normal;
		rayRatio = refractIndex;
		cosine = dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
		cosine = sqrt(1 - refractIndex * refractIndex * (1 - cosine * cosine));
	}
	else
	{
		outWardNormal = rec.normal;
		rayRatio = 1.0 / refractIndex;
		cosine = -dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
	}

	if (refract(rayIn.direction(), outWardNormal, rayRatio, refracted))
	{
		reflectProb = schlick(cosine, refractIndex);
		//scattered = Ray(rec.p, refracted);
	}
	else
	{
		reflectProb = 1.0;
		//scattered = Ray(rec.p, reflected);
	}


	if (drand48() < reflectProb)
	{
		scattered = Ray(rec.p, reflected);
	}
	else
	{
		scattered = Ray(rec.p, refracted);
	}

	return true;
}

diffuseLight::diffuseLight(Texture * a):_emit(a)
{
}

bool diffuseLight::scatter(const Ray & rayIn, const Hit_record & rec, vec3 & attenuation, Ray & scattered) const
{
	return false;
}

vec3 diffuseLight::emitted(float u, float v, const vec3 & p) const
{
	return _emit->value(u, v, p);
}
