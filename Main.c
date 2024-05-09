
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Config.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include "World.h"

#ifdef _WIN32
	#pragma warning (disable : 4996 )
#endif



#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })







int main()
{
	srand(time(NULL));
	printf("start");

	int c = 0;
	for (float r = 0.0f; r < 6.2f; r += 0.1)
	{
		printf("count: %d\n", c);

		
		char name[128];
		sprintf(name, "ppms/img0%03d.ppm", c++);
		FILE* outputFile = fopen(name, "w+");

		if (!outputFile)
		{
			fprintf(stderr, "Could not open file %s\n", name);
			return 1;
		}

		vec3 camPos = vec(2 * sin(r), sin(r) + 1, 2 * cos(r));
		
		struct camera cam = newCam(
			camPos,
			vec(0.0, 0.0, 0.0),
			vec(0.0, 1.0, 0.0),
			90.0f,
			(float)nx / (float)ny
		);

		/*
		struct  camera cam = newCam(
			(vec3) {.x = { 0.0, 0.0, -1.0 }},
			(vec3) {.x = { 0.0, 0.0, 0.0 }},
			(vec3) { { 0.0, 1.0, 0.0 }},
			90.0f,
			(float)nx / (float)ny
		);*/


		//make world
		struct sphere s0 = { .center = (vec3){.x = {0,  0,      0}}, .radius = 0.5, .material = { .type = LAMBERTIAN,	.albedo = (vec3){.x = {0.8, 0.3, 0.3}} } };
		struct sphere s1 = { .center = (vec3){.x = {0,  -100.5, 0}}, .radius = 100, .material = { .type = LAMBERTIAN,	.albedo = (vec3){.x = {0.8, 0.8, 0.0}} } };
		struct sphere s2 = { .center = (vec3){.x = {1,  0,      0}}, .radius = 0.5, .material = { .type = DIELECTRIC,	.albedo = (vec3){.x = {0.8, 0.6, 0.2}}, .refIndex = 1.5} };
		struct sphere s3 = { .center = (vec3){.x = {-1, 0,      0}}, .radius = 0.5, .material = { .type = METAL,		.albedo = (vec3){.x = {0.8, 0.8, 0.8}}, .fuzz = 0.1} };
	
		struct sphere s4 = { .center = addVec3(camPos, mulVec3I(cam.w, 0.55)), .radius = 0.5, .material = {.type = METAL, .albedo = vec(0.1, 0.1, 0.1), .fuzz = 0.7} };

		struct sphere* list[5] = {
			&s0, &s1, &s2, &s3, &s4
		};

		struct world w = { list, (sizeof(list) / sizeof(struct sphere*)) };

		fprintf(outputFile, "P3\n%d %d\n255\n", nx, ny);
		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col = nullVec3;
				for (int s = 0; s < ns; s++)
				{
					float u = (float)(i + rand() / (float)RAND_MAX) / (float)nx;
					float v = (float)(j + rand() / (float)RAND_MAX) / (float)ny;

					ray r = getRay(&cam, u, v);
					col = addVec3(color(&r, &w, 0), col);

				}

				vec3 colScal = divVec3I(col, ns);

				int ir = (int)(255.99 * sqrt(colScal.x[0]));
				int ig = (int)(255.99 * sqrt(colScal.x[1]));
				int ib = (int)(255.99 * sqrt(colScal.x[2]));

				fprintf(outputFile, "%d %d %d\n", ir, ig, ib);
			}

		}





		fclose(outputFile);
	}
		
	return 0;
}
