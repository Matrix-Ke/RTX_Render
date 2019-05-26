// rayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
//#include <cmath>
#include "sphere.h"
#include "hitableList.h"


using namespace std;

#define ImageWidth  400;
#define ImageLength  200;

vec3 color(const Ray& r, Hitable* world)
{
	Hit_record  rec;

	if (world->hit(r, 0, FLT_MAX, rec ))
	{
		return vec3( rec.normal.x() +1 , rec.normal.y()+1, rec.normal.z()+1 )*0.5;
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
	outImage << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);


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
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 col = color(r, world);

			int ir = int(255.99* col[0]);
			int ig = int(255.99* col[1]);
			int ib = int(255.99* col[2]);;
			outImage << ir << " " << ig << " " << ib << "\n";
		}
	}

	cout << "over" << endl;
	return 0;
}
