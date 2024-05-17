#ifndef SPHERE
#define SPHERE

#include <math.h>
#include <stdbool.h>

#include "Ray.h"
#include "Material.h"
#include "Properties.h"
#include "World.h"


struct sphere
{
	vec3 center;
	float radius;

	struct materialProperty material;

	bool isCamera;
};

struct sphere* newSphere(vec3 center, float radius, struct materialProperty material);
bool sphereHit(struct sphere* s, ray* r, float tMin, float tMax, struct hitRecord* rec);

#endif