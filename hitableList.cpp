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
