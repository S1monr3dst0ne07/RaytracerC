#ifndef HWORLD
#define HWORLD

#include <stdbool.h>

#include "Ray.h"
#include "Properties.h"

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

bool worldHit(struct world* w, ray* r, float tMin, float tMax, struct hitRecord* rec);
vec3 color(ray* r, struct world* w, int depth);

#endif