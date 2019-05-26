#pragma once
#include "hitable.h"


class  HitableList : public Hitable
{
private:
	Hitable** listHit;
	int listSize;


public:
	HitableList() {};

	HitableList(Hitable** List, int n) : listHit(List), listSize(n) {};

	virtual bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec) const override;

};