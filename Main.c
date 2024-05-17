
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


	struct world w = newDemoWorld();
	addRandomSpheres(&w);


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

		vec3 camPos = vec(5 * sin(r), 0.5, 5 * cos(r));
		
		vec3 destination = vec(0.0, 0.0, 0.0);
		vec3 origin = camPos;

		struct camera cam = newCam(
			origin,
			destination,
			vec(0.0, 1.0, 0.0),
			90.0f,
			(float)nx / (float)ny,
			0.02f,
			length(subVec3(origin, destination))
		);

		updateCameraSphere(&w, cam);

		/*
		struct  camera cam = newCam(
			(vec3) {.x = { 0.0, 0.0, -1.0 }},
			(vec3) {.x = { 0.0, 0.0, 0.0 }},
			(vec3) { { 0.0, 1.0, 0.0 }},
			90.0f,
			(float)nx / (float)ny
		);*/



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

					struct ray r = getRay(&cam, u, v);
					col = addVec3(color(&r, &w, 0), col);

				}

				vec3 colScal = divVec3I(col, ns);

				int ir = (int)(255.99 * sqrt(colScal._[0]));
				int ig = (int)(255.99 * sqrt(colScal._[1]));
				int ib = (int)(255.99 * sqrt(colScal._[2]));

				fprintf(outputFile, "%d %d %d\n", ir, ig, ib);
			}

		}





		fclose(outputFile);
	}
		
	return 0;
}
