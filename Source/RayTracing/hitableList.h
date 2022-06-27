#pragma once
#include "hitable.h"


class  HitableList : public Hitable
{
private:
	Hitable** _listHit;
	int _listSize;


public:
	HitableList() {};

	HitableList(Hitable** List, int n) : _listHit(List), _listSize(n) {};

	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;

	virtual bool boundingBox(float t0, float t1, AABB& box)  const override;

	int getListSize() const;

	Hitable** getList() const;
};