#include "perlin.h"

float perlin::noise(const vec3 & p) const
{
	float u = p.x() - floor(p.x());
	float v = p.y() - floor((p.y()));
	float w = p.z() - floor(p.z());
	// hermite cubic ����ƽ��
	u = u * u*(3 - 2 * u);
	v = v * v*(3 - 2 * v);
	w = w * w*(3 - 2 * w);
	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());
	
	vec3 c[2][2][2];
	//float  c[2][2][2];
	for (int di = 0; di < 2; di++)
		for (int dj = 0; dj < 2; dj++)
			for (int dk = 0; dk < 2; dk++)
				c[di][dj][dk] = _ranvec[_permX[(i + di) & 255] ^ _permY[(j + dj) & 255] ^ _permZ[(k + dk) & 255]];
	return perlinInterp(c, u, v, w);


}

float perlin::turb(const vec3 & p, int depth) const
{
	float accum = 0;
	vec3 temp_p = p;
	float weight = 1.0;
	for (int i = 0; i < depth; i++)
	{
		accum += weight * noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}
	return fabs(accum);
}


vec3 *perlin::_ranvec = perlinGenerate();
float *perlin::_ranFloat = perlinGenerateF();
int *perlin::_permX = perlinGeneratePerm();
int *perlin::_permY = perlinGeneratePerm();
int *perlin::_permZ = perlinGeneratePerm();





vec3 * perlinGenerate()
{
	vec3 * p = new vec3[256];
	for (int i = 0; i < 256; ++i)
		p[i] = makeUnitVector(vec3(-1 + 2 * drand48(), -1 + 2 * drand48(), -1 + 2 * drand48()));
	return p;
}

float * perlinGenerateF()
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

inline float triLinearInterp(float cp[2][2][2], float u, float v, float w)
{
	float accum = 0;
	for (int i = 0; i < 2; i++) 
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				accum += (i * u + (1 - i) * (1 - u)) * (j * v + (1 - j) * (1 - v)) * (k * w + (1 - k) * (1 - w)) *
					cp[i][j][k];
			}
		}
	}
	return accum;
}

inline float perlinInterp(vec3 c[2][2][2], float u, float v, float w)
{
	float uu = u * u*(3 - 2 * u);
	float vv = v * v*(3 - 2 * v);
	float ww = w * w*(3 - 2 * w);
	float accum = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				vec3 weight_v(u - i, v - j, w - k);
				accum += (i*uu + (1 - i)*(1 - uu))*
					(j*vv + (1 - j)*(1 - vv))*
					(k*ww + (1 - k)*(1 - ww))*dot(c[i][j][k], weight_v);
			}
	return accum;
}