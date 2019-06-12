#include "rectangle.h"




xyRect::xyRect(float _x0, float _x1, float _y0, float _y1, float _k, Material * mat)
					: _x0(_x0), _x1(_x1), _y0(_y0), _y1(_y1), _k(_k), _mPtr(mat) {};

// 
bool xyRect::hit(const Ray& r, float t0, float t1, Hit_record& rec) const {
	float t = (_k - r.origin().z()) / r.direction().z();
	if (t < t0 || t > t1)
		return false;
	float x = r.origin().x() + t * r.direction().x();
	float y = r.origin().y() + t * r.direction().y();
	if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
		return false;
	rec.u = (x - _x0) / (_x1 - _x0);
	rec.v = (y - _y0) / (_y1 - _y0);
	rec.t = t;
	rec.matPtr = _mPtr;
	rec.p = r.pointAtParameter(t);
	rec.normal = vec3(0, 0, 1);
	return true;
}

bool xyRect::boundingBox(float t0, float t1, AABB & box) const
{
	box = AABB(vec3(_x0, _y0, _k - 0.0001), vec3(_x1, _y1, _k + 0.0001));
	return true;
}


bool xzRect::boundingBox(float t0, float t1, AABB & box) const
{
	box = AABB(vec3(_x0, _k - 0.0001, _z0), vec3(_x1, _k + 0.0001, _z1));
	return true;
}

xzRect::xzRect(float _x0, float _x1, float _z0, float _z1, float _k, Material * mat)
				: _x0(_x0), _x1(_x1), _z0(_z0), _z1(_z1), _k(_k), _mPtr(mat) {};

bool xzRect::hit(const Ray& r, float t0, float t1, Hit_record& rec) const {
	float t = (_k - r.origin().y()) / r.direction().y();
	if (t < t0 || t > t1)
		return false;
	float x = r.origin().x() + t * r.direction().x();
	float z = r.origin().z() + t * r.direction().z();
	if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
		return false;
	rec.u = (x - _x0) / (_x1 - _x0);
	rec.v = (z - _z0) / (_z1 - _z0);
	rec.t = t;
	rec.matPtr = _mPtr;
	rec.p = r.pointAtParameter(t);
	rec.normal = vec3(0, 1, 0);
	return true;
}

yzRect::yzRect(float _y0, float _y1, float _z0, float _z1, float _k, Material * mat)
					: _y0(_y0), _y1(_y1), _z0(_z0), _z1(_z1), _k(_k), _mPtr(mat) {};

bool yzRect::hit(const Ray& r, float t0, float t1, Hit_record& rec) const {
	float t = (_k - r.origin().x()) / r.direction().x();
	if (t < t0 || t > t1)
		return false;
	float y = r.origin().y() + t * r.direction().y();
	float z = r.origin().z() + t * r.direction().z();
	if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
		return false;
	rec.u = (y - _y0) / (_y1 - _y0);
	rec.v = (z - _z0) / (_z1 - _z0);
	rec.t = t;
	rec.matPtr = _mPtr;
	rec.p = r.pointAtParameter(t);
	rec.normal = vec3(1, 0, 0);
	return true;
}

bool yzRect::boundingBox(float t0, float t1, AABB & box) const
{
	box = AABB(vec3(_k - 0.0001, _y0, _z0), vec3(_k + 0.0001, _y1, _z1));
	return true;
}
