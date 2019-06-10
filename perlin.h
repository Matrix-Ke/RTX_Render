#pragma once
#include "Vec3.h"
#include "drand48.h"

class perlin
{
public:
	float noise(const vec3& p) const;

	// �����Ŷ�
	float turb(const vec3& p, int depth = 7) const;

private:
	static vec3*    _ranvec;
	static float*	_ranFloat;
	static int*		_permX;
	static int*		_permY;
	static int*		_permZ;

};





static vec3* perlinGenerate();

static float* perlinGenerateF();

// �ı����к���
void	permute(int* p, int n);

static int* perlinGeneratePerm();


inline float triLinearInterp(float cp[2][2][2], float u, float v, float w);

inline float perlinInterp(vec3 c[2][2][2], float u, float v, float w);
