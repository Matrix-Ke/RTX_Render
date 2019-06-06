#include "hitable.h"

BvhNode::BvhNode()
{
}

BvhNode::BvhNode(Hitable ** l, int n, float time0, float time1)
{
}

bool BvhNode::hit(const Ray & r, float tmin, float tmax, Hit_record & rec) const
{
		if (box.hit(r, tmin, tmax))
		{
			Hit_record leftRec, rightRec;
			bool	hitLeft = _left->hit(r, tmin, tmax, leftRec);
			bool	hitRight = _right->hit(r, tmin, tmax, rightRec);
			if (hitLeft && hitRight)
			{
				if (leftRec.t < rightRec.t)
					rec = leftRec;
				else
					rec = rightRec;
				return true;
			}
			else if (hitLeft)
			{
				rec = leftRec;
				return true;
			}
			else if (hitRight)
			{
				rec = rightRec;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	return false;
}


int boxCompare(const void* a, const void* b)
{
	AABB boxLeft, boxRight;
	Hitable* ah = *(Hitable**)a;
	Hitable* bh = *(Hitable**)b;

	if ((!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight)))
	{
		std::cout << " No bouding box, in BvhNode constructor\n";
	}
	if (boxLeft.min().x() - boxRight.min().x() < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}