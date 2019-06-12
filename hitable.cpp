#include "hitable.h"

void getSphereUV(const vec3 & p, float & u, float & v)
{
	float phi = atan2(p.z(), p.x());
	float theta = asin(p.y());
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

bool flipNormals::hit(const Ray & r, float t_min, float t_max, Hit_record & rec) const
{
	if (ptr->hit(r, t_min, t_max, rec)) {
		rec.normal = -rec.normal;
		return true;
	}
	else
		return false;
}

bool flipNormals::boundingBox(float t0, float t1, AABB & box) const
{
	return ptr->boundingBox(t0, t1, box);
}
