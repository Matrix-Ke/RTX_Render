#pragma once

#include "texture.h"

class ImageTexture :public Texture
{
public:
	ImageTexture();
	ImageTexture(unsigned char *pixels, int A, int B) ;
	virtual vec3 value(float u, float v, const vec3& p) const override;


private:
	unsigned char*	_data;
	int _nx;
	int _ny;
};
