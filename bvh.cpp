#include <iostream>
#include "bvh.h"
#include "drand48.h"

BvhNode::BvhNode()
{
}

BvhNode::BvhNode(Hitable ** list, int n, float time0, float time1)
{
	int randomAxis = int(3 * drand48());
	if (randomAxis == 0)
	{
		qsort(list, n, sizeof(Hitable*), boxXCompare);
	}
	else if (randomAxis == 1)
	{
		qsort(list, n, sizeof(Hitable*), boxYCompare);
	}
	else
	{
		qsort(list, n, sizeof(Hitable*), boxZCompare);
	}
	if (n == 1)
	{
		_left = _right = list[0];
	}
	else if (n == 2)
	{
		_left = list[0];
		_right = list[1];
	}
	else
	{
		_left = new BvhNode(list, n / 2, time0, time1);
		_right = new BvhNode(list + n / 2, n - n / 2, time0, time1);
	}

	AABB   boxLeft, boxRight;
	if (!_left->boundingBox(time0, time1, boxLeft) || !_right->boundingBox(time0, time1, boxRight))
	{
		std::cerr << " no bounding Box in bvhNode constructor \n";
	}
	_box = surroundingBox(boxLeft, boxRight);

}

bool BvhNode::hit(const Ray & r, float tmin, float tmax, Hit_record & rec) const
{
	if (_box.hit(r, tmin, tmax))
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
			return true;
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
}

bool BvhNode::boundingBox(float t0, float t1, AABB & box) const
{
	box = _box;
	return true;
}


int boxXCompare(const void* a, const void* b)
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

int boxYCompare(const void * a, const void * b)
{
	AABB boxLeft, boxRight;
	Hitable* ah = *(Hitable**)a;
	Hitable* bh = *(Hitable**)b;

	if ((!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight)))
	{
		std::cout << " No bouding box, in BvhNode constructor\n";
	}
	if (boxLeft.min().y() - boxRight.min().y() < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int boxZCompare(const void * a, const void * b)
{
	AABB boxLeft, boxRight;
	Hitable* ah = *(Hitable**)a;
	Hitable* bh = *(Hitable**)b;

	if ((!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight)))
	{
		std::cout << " No bouding box, in BvhNode constructor\n";
	}
	if (boxLeft.min().z() - boxRight.min().z() < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
