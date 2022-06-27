#pragma once
#include "Hitable.h"

// xy平面的矩形
class xyRect : public Hitable 
{
public:
	xyRect() {}
	xyRect(float _x0, float _x1, float _y0, float _y1, float _k, Material *mat);

	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;

	virtual bool boundingBox(float t0, float t1, AABB& box)  const override;

private:

	Material  *_mPtr;
	float _x0, _x1, _y0, _y1, _k;
};

class xzRect : public Hitable 
{
public:
	xzRect() {}
	xzRect(float _x0, float _x1, float _z0, float _z1, float _k, Material *mat);

	virtual bool hit(const Ray& r, float t0, float t1, Hit_record& rec) const override;

	virtual bool boundingBox(float t0, float t1, AABB& box)  const override;

	Material  *_mPtr;

	float _x0, _x1, _z0, _z1, _k;
};

class yzRect : public Hitable 
{
public:
	yzRect() {}
	yzRect(float _y0, float _y1, float _z0, float _z1, float _k, Material *mat);

	virtual bool hit(const Ray& r, float t0, float t1, Hit_record& rec) const override;

	virtual bool boundingBox(float t0, float t1, AABB& box) const override;

	Material  *_mPtr;

	float _y0, _y1, _z0, _z1, _k;
};


