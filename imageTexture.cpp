#include "imageTexture.h"

ImageTexture::ImageTexture()
{
}

ImageTexture::ImageTexture(unsigned char * pixels, int A, int B) : _data(pixels), _nx(A), _ny(B) 
{
}

vec3 ImageTexture::value(float u, float v, const vec3 & p) const
{
	int i = (1 - u)*_nx;
	int j = (1 - v)*_ny - 0.001;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > _nx - 1) i = _nx - 1;
	if (j > _ny - 1) j = _ny - 1;
	float r = int(_data[3 * i + 3 * _nx*j]) / 255.0;
	float g = int(_data[3 * i + 3 * _nx*j + 1]) / 255.0;
	float b = int(_data[3 * i + 3 * _nx*j + 2]) / 255.0;
	return vec3(r, g, b);
}
