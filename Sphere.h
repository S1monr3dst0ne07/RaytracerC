#ifndef SPHERE
#define SPHERE

#include "Ray.h"
#include "Material.h"
#include "Properties.h"
#include "World.h"

#include <math.h>
#include <stdbool.h>


struct sphere
{
	vec3 center;
	float radius;

	struct materialProperty material;
};

bool sphereHit(struct sphere* s, ray* r, float tMin, float tMax, struct hitRecord* rec);

#endif