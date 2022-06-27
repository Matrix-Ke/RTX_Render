// rayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma once
#include <iostream>
#include <fstream>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "imageTexture.h"
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "Material.h"
#include "bvh.h"
#include "rectangle.h"

#define ImageWidth  200
#define ImageLength  200
#define  RecursionDepth	10
#define	samplePixel	100;
#define random(a, b)   (rand()%(b - a +1 ) +a )

using namespace std;


HitableList*  randomScene()
{
	int n = 50;
	Hitable **list = new Hitable *[n + 1];

	Texture* checker = new CheckerTexture(new ConstantTexture(vec3(0.2, 0.3, 0.1)), new ConstantTexture(vec3(0.9, 0.9, 0.9)));
	list[0] = new sphere(vec3(0, -701, 0), 700, new lambertian( checker ) );
	int i = 1;
	for (int a = -3; a < 3; a++) 
	{
		for (int b = -3; b < 3; b++)
		{
			float chooseMat = drand48();
			vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (chooseMat < 0.7) 
				{  // diffuse
					// 运动模糊的小球
					list[i++] = new MovingSphere(center, center + vec3(0, 0.5 * drand48(), 0), 0.0, 1.0, 0.2,
						new lambertian( new ConstantTexture( vec3(drand48(), drand48(), drand48())  )));
				}
				else if (chooseMat < 0.95) 
				{ // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(2.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian( new ConstantTexture( vec3(0.4, 0.2, 0.1)) ) );
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(1, 1, 1), 0.0));

	////fix bvhnode hit debug code
	//list[i++] = new sphere(vec3(0, 0, -10), 1.0, new dielectric(2.5));
	//list[i++] = new sphere(vec3(-2, 0, -10), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	//list[i++] = new sphere(vec3(2, 0, -10), 1.0, new metal(vec3(1, 1, 1), 0.0));

	return new HitableList(list, i);
}

Hitable *earth() 
{
	int nx, ny, nn;
	unsigned char *texData = stbi_load("picture.png", &nx, &ny, &nn, 0);
	if (texData == nullptr)
	{
		cout << " picture load fail \n";
	}
	cout << nx << "  " << ny << "  " << nn << endl;
	Material *mat = new lambertian(new ImageTexture(texData, nx, ny));
	return new sphere(vec3(0, 2, 0), 2, mat);
}

HitableList *twoPerlinSpheres()
{
	Texture *pertext = new noiseTexture();
	Hitable **list = new Hitable*[2];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
	//list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
	list[1] = earth();
	return new HitableList(list, 2);
}


// rectangle & light 
Hitable *simpleLight() {
	Texture *pertext = new noiseTexture(4);
	Texture *checker = new CheckerTexture(new ConstantTexture(vec3(0.2, 0.3, 0.1)),
		new ConstantTexture(vec3(0.9, 0.9, 0.9)));
	Hitable **list = new Hitable *[4];
	list[0] = new sphere(vec3(0, -700, 0), 700, new lambertian(checker));
	list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
	list[2] = new sphere(vec3(0, 7, 0), 2, new diffuseLight(new ConstantTexture(vec3(4, 4, 4))));
	list[3] = new xyRect(3, 5, 1, 3, -2, new diffuseLight(new ConstantTexture(vec3(4, 4, 4))));
	return new HitableList(list, 4);
}

Hitable *test() {
	Texture *pertext = new noiseTexture(4);
	Texture *checker = new CheckerTexture(new ConstantTexture(vec3(0.2, 0.3, 0.1)),
		new ConstantTexture(vec3(0.9, 0.9, 0.9)));
	Hitable **list = new Hitable *[4];
	list[0] = new sphere(vec3(0, -700, 0), 700, new lambertian(checker));
	list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
	list[2] = new sphere(vec3(0, 7, 0), 2, new diffuseLight(new ConstantTexture(vec3(11, 11, 11))));
	//    list[3] = new xyRect(3,5,1,3,-2,new diffuseLight(new ConstantTexture(vec3(4,4,4))));
	return new HitableList(list, 3);
}

// cornellBox
Hitable *cornellBox() {
	Hitable **list = new Hitable*[8];
	int i = 0;
	Material *red = new lambertian(new ConstantTexture(vec3(0.65, 0.05, 0.05)));
	Material *white = new lambertian(new ConstantTexture(vec3(0.73, 0.73, 0.73)));
	Material *green = new lambertian(new ConstantTexture(vec3(0.12, 0.45, 0.15)));
	Material *light = new diffuseLight(new ConstantTexture(vec3(15, 15, 15)));
	//x range from(0, 555)
	list[i++] = new yzRect(0, 555, 0, 555, 0, red);
	list[i++] = new flipNormals(new yzRect(0, 555, 0, 555, 555, green));
	//y range from(0, 555)
	list[i++] = new xzRect(213, 343, 227, 332, 554, light);
	list[i++] = new flipNormals(new xzRect(0, 555, 0, 555, 555, white));
	list[i++] = new xzRect(0, 555, 0, 555, 0, white);

	//z range from( ? , 555)
	list[i++] = new flipNormals(new xyRect(0, 555, 0, 555, 555, white));
	return new HitableList(list, i);
}

vec3 color(const Ray& r, Hitable* world, int depth)
{
	Hit_record  rec;

	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		vec3 attenuation;

		// emissive
		vec3	emitted = rec.matPtr->emitted(rec.u, rec.v, rec.p);

		if (depth < RecursionDepth && rec.matPtr->scatter(r, rec, attenuation, scattered))
		{
			return emitted + attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			//return vec3(0.0, 0.0, 0.0);
			return emitted;
		}
	}
	else
	{
		//vec3 unitDir = r.direction();
		//unitDir.makeUnitVector();
		//float t = 0.5 * (unitDir.y() + 1.0);
		//return vec3(1.0, 1.0, 1.0)*(1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
		//cout << " hit ";
		return vec3(0, 0, 0);
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


	vec3 lookfrom(278, 278, -800);
	vec3 lookat(278, 278, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;
	float vfov = 40.0;
	camera renderCamera(lookfrom, lookat, vec3(0, 1, 0), vfov, float(nx) / float(ny), aperture, dist_to_focus, 0.0, 1.0);


	//random_device rd;
	Hitable* world = cornellBox();
	//int size = world->getListSize();
	//Hitable**  allObject = world->getList();
	//BvhNode*   root = new BvhNode(allObject, size, 0.0f, 1.0f);

	for (int j = ny - 1 ; j >= 0; j--)
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
	outImage.close();
	cout << "over finished" << endl;
	return 0;
}
