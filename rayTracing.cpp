// rayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#define ImageWidth  200;
#define ImageLength  100;
#define random(a, b)   (rand()%(b - a +1 ) +a )
#define randomNum	(float((rand()%100)) /100.0f)
//#define randomNum (float((rand()%(100)))/100.0f)
using namespace std;




vec3 randomPointInUintsphere()
{
	vec3  point;
	do
	{
		point = 2.0 * vec3(randomNum, randomNum, randomNum) - vec3(1, 1, 1);
	} while ( dot(point, point) >= 1.0);
	return point;
}


vec3 color(const Ray& r, Hitable* world)
{
	Hit_record  rec;

	if (world->hit(r, 0, FLT_MAX, rec ))
	{
		vec3   diffuseDir = rec.normal + randomPointInUintsphere();

		return 0.5 * color(Ray(rec.p, diffuseDir), world);
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
	int ns = 10;

	outImage << "P3\n" << nx << " " << ny << "\n255\n";
	camera    renderCamera;

	


	Hitable *list[2];
	// 球1
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	// 球2
	list[1] = new sphere(vec3(0, -100.5, -1), 100);      
	Hitable* world = new HitableList(list, 2);
	 




	for (int j = ny -1 ; j >= 0 ; j--)
	{   
		for (int i = 0; i < nx; i++)
		{
			vec3   pixelColor(0.0, 0.0, 0.0);

			for (int k = 0; k < ns; k++)
			{

				float u = (float(i) + float(random(0, 100)) / 100.0f) / float(nx);
				float v = (float(j) + float(random(0, 100)) / 100.0f) / float(ny);

				Ray  r = renderCamera.getRay(u, v);

				pixelColor += color(r, world);
			}
			pixelColor /= (float)ns;

			int ir = int(255.99* pixelColor[0]);
			int ig = int(255.99* pixelColor[1]);
			int ib = int(255.99* pixelColor[2]);
			outImage << ir << " " << ig << " " << ib << "\n";
		}
	}

	cout << "over" << endl;
	return 0;
}
