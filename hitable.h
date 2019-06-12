#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ray.h"
#include "aabb.h"

class Material;


void getSphereUV(const vec3& p, float& u, float& v);

struct Hit_record
{
	float t;
	float u;
	float v;
	vec3  p;
	vec3 normal;
	Material* matPtr;
};


class Hitable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const = 0;

	//add boundingbox for AABB algorithem
	virtual bool boundingBox(float t0, float t1, AABB& box)  const = 0;

private:

};


//flip face Normal 
class flipNormals : public Hitable {
public:
	flipNormals(Hitable *p) : ptr(p) {}
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;
	virtual bool boundingBox(float t0, float t1, AABB& box) const override;

private:

	Hitable *ptr;
};


