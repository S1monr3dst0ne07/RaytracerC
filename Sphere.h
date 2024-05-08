#ifndef SPHERE
#define SPHERE

#include <math.h>
#include "Ray.h"
#include <stdbool.h>

struct hitRecord
{
	float t;
	vec3 p;
	vec3 normal;
	vec3 albedo;
	char materialType;
};

struct sphere
{
	vec3 center;
	float radius;
	char materialType;
	vec3 albedo;
};

struct world
{
	struct sphere** list;
	int size;

};


bool sphereHit(struct sphere* s, ray* r, float tMin, float tMax, struct hitRecord* rec);
bool worldHit(struct world* w, ray* r, float tMin, float tMax, struct hitRecord* rec);

#endif