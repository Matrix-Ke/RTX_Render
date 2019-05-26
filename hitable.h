#pragma once

#include "ray.h"

class Material;

struct Hit_record
{
	float t;
	vec3  p;
	vec3 normal;
	Material* matPtr;
};


class Hitable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const = 0;
private:

};
