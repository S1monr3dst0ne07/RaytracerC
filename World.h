#ifndef HWORLD
#define HWORLD

#include <stdbool.h>

#include "Ray.h"
#include "Properties.h"
#include "Camera.h"

struct world
{
	struct sphere** list;
	int size;

};

struct hitRecord
{
	float t;
	vec3 p;
	vec3 normal;

	struct materialProperty material;
};

struct world newDemoWorld();
void addRandomSpheres(struct world* w);
void updateCameraSphere(struct world* w, struct camera cam);

bool worldHit(struct world* w, struct ray* r, float tMin, float tMax, struct hitRecord* rec);
vec3 color(struct ray* r, struct world* w, int depth);

#endif