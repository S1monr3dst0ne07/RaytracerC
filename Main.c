
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <pthread.h>

#include "Material.h"
#include "Camera.h"

#pragma warning (disable : 4996 )

const int ns = 5;
const int nx = 1920;
const int ny = 1080;
//#define thrCnt 2048

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


vec3 color(ray* r, struct world* w, int depth)
{
	vec3 output = { .x = {0.5f, 0.7f, 1.0f} };
	struct hitRecord rec;
	rec.normal = nullVec3;
	rec.p	   = nullVec3;
	rec.t = 0;

	if (worldHit(w, r, 0.00001, 10000000.0, &rec))
	{
		struct materialReturn mR;
		mR.bounce    = false;
		mR.atten     = nullVec3;
		mR.scattered = (ray){ .A = nullVec3, .B = nullVec3 };

		switch (rec.materialType)
		{
		case LAMBERTIAN: 
			mR = lambertian(r, &rec);
			break;
		case METAL:
			mR = metal(r, &rec);
			break;
		}

		if (depth < 3 && mR.bounce)
		{
			vec3 bounceColor = color(&mR.scattered, w, depth + 1);
			output = mulVec3(mR.atten, bounceColor);
		}
	}

	return output;
}



/*

struct lineData
{
	int lineIndex;
	struct camera cam;
	struct world* w;
	char* lineBuffer; //needs to have length of 3 * nx
};

void* renderLine(void* args)
{
	struct lineData ld = *(struct lineData*)(args);
	int j = ld.lineIndex;
	for (int i = 0; i < nx; i++)
	{
		vec3 col = nullVec3;
		for (int s = 0; s < ns; s++)
		{
			float u = (float)(i + (rand() / (float)RAND_MAX * 0.0f)) / (float)nx;
			float v = (float)(j + (rand() / (float)RAND_MAX * 0.0f)) / (float)ny;
			//float u = i / (float)nx;
			//float v = j / (float)ny;

			ray r = getRay(&ld.cam, u, v);
			col = addVec3(color(&r, ld.w, 0), col);

		}

		vec3 colScal = divVec3I(col, ns);

		char* lb = &ld.lineBuffer[i * 3];

		//processing for channel
		#define chnl(c) lb[c] = (char)(255.99 * sqrt(colScal.x[c]));
		chnl(0)
		chnl(1)
		chnl(2)
		#undef chnl
	}

	return NULL;
}

pthreads
pthread_t thr[thrCnt];
struct lineData ld[ny];


int main() 
{
	srand(time(NULL));
	printf("start");

	struct camera cam = {
		.lowerLeftCorner = (vec3){.x = { -2.0 * 2, -1.0 * 2, -1.0} },
		.hori            = (vec3){.x = { 4.0 * 2, 0.0, 0.0} },
		.vert            = (vec3){.x = { 0.0, 2.0 * 2, 0.0} },
		.origin          = (vec3){.x = { 0.0, 0.0, 0.0} }
	};

	//make world
	struct sphere s0 = { .center = (vec3){.x = {0, 0, -1}},		 .radius = 0.5,	.materialType = LAMBERTIAN,	.albedo = (vec3){.x = {0.8, 0.3, 0.3}} };
	struct sphere s1 = { .center = (vec3){.x = {0, -100.5, -1}}, .radius = 100,	.materialType = LAMBERTIAN,	.albedo = (vec3){.x = {0.8, 0.8, 0.0}} };
	struct sphere s2 = { .center = (vec3){.x = {1, 0, -1}},		 .radius = 0.5, .materialType = METAL,		.albedo = (vec3){.x = {0.8, 0.6, 0.2}} };
	struct sphere s3 = { .center = (vec3){.x = {-1, 0, -1}},	 .radius = 0.5,	.materialType = METAL,		.albedo = (vec3){.x = {0.8, 0.8, 0.8}} };
	struct sphere* list[4] = {
		&s0, &s1, &s2, &s3
	};
	struct world w = { list, (sizeof(list) / sizeof(struct sphere*)) };


	//framebuffer
	int frameSize = ny * nx * 3;
	char* frameBuffer = malloc(frameSize);
	if (!frameBuffer) return 1;

	int thrI = 0;
	for (int lineIndex = ny - 1; lineIndex >= 0; lineIndex--)
	{
		printf("start: %d\n", lineIndex);

		ld[lineIndex] = (struct lineData){
			.lineIndex = lineIndex, 
			.cam = cam,
			.w = &w,
			.lineBuffer = &frameBuffer[(ny - lineIndex - 1) * nx * 3]
		};

		renderLine(&ld[lineIndex]);

	}

	FILE* outputFile = fopen("Img.ppm", "wb");

	fprintf(outputFile, "P6\n%d %d\n255\n", nx, ny);
	fwrite(frameBuffer, sizeof(char), frameSize, outputFile);

	fclose(outputFile);
	//free(frameBuffer);

	return 0;
}
*/



int main()
{
	srand(time(NULL));
	printf("start");

	FILE* OutputFile;
	OutputFile = fopen("Img.ppm", "w+");

	struct camera cam = {
		.lowerLeftCorner = (vec3){.x = { -2.0, -1.0, -1.0} },
		.hori = (vec3){.x = { 4.0, 0.0, 0.0} },
		.vert = (vec3){.x = { 0.0, 2.0, 0.0} },
		.origin = (vec3){.x = { 0.0, 0.0, 0.0} }
	};


	//make world
	struct sphere s0 = { .center = (vec3){.x = {0, 0, -1}},		 .radius = 0.5,	.materialType = LAMBERTIAN,	.albedo = (vec3){.x = {0.8, 0.3, 0.3}} };
	struct sphere s1 = { .center = (vec3){.x = {0, -100.5, -1}}, .radius = 100,	.materialType = LAMBERTIAN,	.albedo = (vec3){.x = {0.8, 0.8, 0.0}} };
	struct sphere s2 = { .center = (vec3){.x = {1, 0, -1}},		 .radius = 0.5, .materialType = METAL,		.albedo = (vec3){.x = {0.8, 0.6, 0.2}} };
	struct sphere s3 = { .center = (vec3){.x = {-1, 0, -1}},	 .radius = 0.5,	.materialType = METAL,		.albedo = (vec3){.x = {0.8, 0.8, 0.8}} };
	struct sphere* list[4] = {
		&s0, &s1, &s2, &s3
	};

	struct world w = { list, (sizeof(list) / sizeof(struct sphere*)) };

	fprintf(OutputFile, "P3\n%d %d\n255\n", nx, ny);
	for (int j = ny - 1; j >= 0; j--)
	{
		printf("Row: %d\n", j);
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

			fprintf(OutputFile, "%d %d %d\n", ir, ig, ib);
		}
		printf("");
	}





	fclose(OutputFile);
	return 0;
}