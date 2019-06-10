#pragma once

#include "hitable.h"


class sphere : public Hitable
{
private:
	vec3		_center;
	float		_radius;
	Material*	_matPtr;
	AABB		_box;

public:
	sphere() {};
	sphere(const vec3& cen, const float r, Material* mPtr = nullptr);
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;
	//  add boudingBox
	virtual bool boundingBox(float t0, float t1, AABB& box) const override;

};

class MovingSphere : public Hitable
{
public:
	MovingSphere();
	MovingSphere(const vec3& cen1, const vec3& cen2, float sTime, float eTime, float R, Material * mat) ;

	vec3  center(const float time) const;
	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;
	
	//add boudingBox
	virtual bool boundingBox(float t0, float t1, AABB& box) const override;

private:
	AABB surrounding_box(AABB &box0, AABB &box1) const;

private:
	vec3    _centerPos1;
	vec3	_centerPos2;
	float	_startTime;
	float	_endTime;
	float	_radius;
	Material*  _matPtr;
};