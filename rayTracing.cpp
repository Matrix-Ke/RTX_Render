// rayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma once
#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "material.h"
#define ImageWidth  200
#define ImageLength  100
#define  RecursionDepth	10
#define	samplePixel	100;
#define random(a, b)   (rand()%(b - a +1 ) +a )
//#define randomNum	(float((rand()%100)) /100.0f)
//#define randomNum (float((rand()%(100)))/100.0f)
using namespace std;


vec3 color(const Ray& r, Hitable* world, int depth)
{
	Hit_record  rec;

	if (world->hit(r, 0, FLT_MAX, rec))
	{
		Ray scattered;
		vec3 attenuation;
		if (depth < RecursionDepth && rec.matPtr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0.0, 0.0, 0.0);
		}
	}
	else
	{
		vec3 unitDir = r.direction();
		unitDir.makeUnitVector();
		float t = 0.5 * (unitDir.y() + 1.0);
		return vec3(1.0, 1.0, 1.0)*(1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
	}
}


int main()
{
	ofstream   outImage("./Image/picture_1.ppm", ios::out);
	if (!outImage)
	{
		cout << "open file error" << endl;
	}
	int nx = ImageWidth;
	int ny = ImageLength;
	int ns = samplePixel;

	outImage << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lookfrom(3, 3, 2);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 2.0;
	camera renderCamera(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	Hitable *list[4];
	// 球1,2,3,4; 2个lambertian ，2个metal
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));

	Hitable *world = new HitableList(list, 4);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3   pixelColor(0.0, 0.0, 0.0);
			for (int k = 0; k < ns; k++)
			{
				float u = (float(i) + float(random(0, 100)) / 100.0f) / float(nx);
				float v = (float(j) + float(random(0, 100)) / 100.0f) / float(ny);
				Ray  r = renderCamera.getRay(u, v);

				pixelColor += color(r, world, 0);
			}
			pixelColor /= (float)ns;
			pixelColor = vec3(sqrt(pixelColor[0]), sqrt(pixelColor[1]), sqrt(pixelColor[2]));

			int ir = int(255.99* pixelColor[0]);
			int ig = int(255.99* pixelColor[1]);
			int ib = int(255.99* pixelColor[2]);
			outImage << ir << " " << ig << " " << ib << "\n";
		}
	}
	cout << "over finished" << endl;
	return 0;
}
