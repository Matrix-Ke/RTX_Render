#include "hitableList.h"

bool HitableList::hit(const Ray & r, float t_min, float t_max, Hit_record & rec) const
{
		Hit_record  tempRec;
		bool  hitAnything = false;
		float closetGeometryParam = t_max;
		for (int i = 0; i < listSize; i++)
		{
			if (listHit[i]->hit(r, t_min, closetGeometryParam, tempRec))
			{
				hitAnything = true;
				closetGeometryParam = tempRec.t;
				rec = tempRec;
			}
		}
	
		return hitAnything;
}

bool HitableList::boundingBox(float t0, float t1, AABB & box) const
{
	if (listSize < 1)
		return false;
	AABB	tempBox;
	bool	firstTrue = listHit[0]->boundingBox(t0, t1, tempBox);
	if (!firstTrue)
		return false;
	else
		box = tempBox;

	for (int i = 0; i < listSize; i++)
	{
		if (listHit[0]->boundingBox(t0, t1, tempBox))
		{
			box = surroundingBox(box, tempBox);
		}
		else
		{
			return false;
		}
	}
	return true;
}
