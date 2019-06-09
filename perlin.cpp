#include "perlin.h"

float perlin::noise(const vec3 & p) const
{
	//float u = p.x() - floor(p.x());
	//float v = p.y() - floor((p.y()));
	//float z = p.z() - floor(p.z());

	int i = int(4 * p.x()) & 255;
	int j = int(4 * p.y()) & 255;
	int k = int(4 * p.z()) & 255;

	return _ranFloat[_permX[i] ^ _permY[j] ^ _permY[k]];

}



float *perlin::_ranFloat = perlinGenerate();
int *perlin::_permX = perlinGeneratePerm();
int *perlin::_permY = perlinGeneratePerm();
int *perlin::_permZ = perlinGeneratePerm();



float * perlinGenerate()
{
	float* p = new float[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = drand48();
	}
	return p;
}

void permute(int * p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = int(drand48()*(i + 1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

int * perlinGeneratePerm()
{
	int* p = new int[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = i;
	}
	permute(p, 256);
	return p;
}
