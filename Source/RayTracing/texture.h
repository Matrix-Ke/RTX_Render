#pragma once
#include "Vec3.h"
#include "perlin.h"



class Texture
{
public:
	virtual vec3 value(float u, float v, const vec3& p) const = 0;

};



class ConstantTexture :public Texture
{
public:
	ConstantTexture();

	ConstantTexture(const vec3& color);
	virtual vec3 value(float u, float v, const vec3& p) const override;

private:
	vec3	_color;
};



class CheckerTexture : public Texture
{
public:
	CheckerTexture();
	CheckerTexture(Texture* t0, Texture* t1);

	virtual vec3 value(float u, float v, const vec3& p) const override;


private:
	Texture*	_odd;
	Texture*	_even;
};

class noiseTexture : public Texture
{
public:
	noiseTexture();

	noiseTexture(float sc);

	virtual vec3 value(float u, float v, const vec3& p) const override;

private:
	perlin  _noise;
	float   _scale;
};



