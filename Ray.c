#include "Ray.h"

/*
ray* newRay(vec3 A, vec3 B)
{
	ray* output = (ray*)malloc(sizeof(ray));
	output->A = A;
	output->B = B;

	return output;
}*/

vec3 pap(ray* r, float t)
{
	return addVec3(mulVec3I(r->B, t), r->A);
}

