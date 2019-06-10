#include <iostream>

#include "texture.h"

ConstantTexture::ConstantTexture()
{
}

ConstantTexture::ConstantTexture(const vec3 & color) :_color(color) 
{
}

vec3 ConstantTexture::value(float u, float v, const vec3 & p) const
{
	return _color;
}

CheckerTexture::CheckerTexture()
{
}

CheckerTexture::CheckerTexture(Texture * t0, Texture * t1) : _odd(t1), _even(t0)
{
}

vec3 CheckerTexture::value(float u, float v, const vec3 & p) const
{
	float sines = sin( 5 * p.x()) * sin(5 * p.y()) * sin(5 * p.z());
	if ( sines < 0.0f )
	{
		return _odd->value(u, v, p);
	}
	else
	{
		return _even->value(u, v, p);
	}
}

noiseTexture::noiseTexture()
{
	_scale = 2.5f;
}

noiseTexture::noiseTexture(float sc):_scale(sc)
{
}

vec3 noiseTexture::value(float u, float v, const vec3 & p) const
{
	//return vec3(1, 1, 1)*_noise.noise(p);
	//return vec3(1, 1, 1)*_noise.noise(_scale*p);
	//return vec3(1, 1, 1)*_noise.turb(_scale*p);
	//return vec3(1, 1, 1) * 0.5 * (1 + _noise.turb(_scale* p));
	 // �����ź��Ŷ���
	return vec3(1, 1, 1)*0.5*(1 + sin(_scale*p.z() + 10 * _noise.turb(_scale*p)));

}


