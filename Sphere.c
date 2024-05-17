
#include "Material.h"
#include "Sphere.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


struct sphere* newSphere(vec3 center, float radius, struct materialProperty material)
{
	struct sphere* s = malloc(sizeof(struct sphere));
	s->center = center;
	s->radius = radius;
	s->material = material;
	s->isCamera = false;

	return s;
}


bool sphereHit(struct sphere* s, struct ray* r, float tMin, float tMax, struct hitRecord* rec)
{
	vec3 oc = subVec3(r->origin, s->center);
	//float a = dotVec3(r->direction, r->direction);
	float a = r->dot;
	float b = dotVec3(oc, r->direction);
	float c = dotVec3(oc, oc) - s->radius * s->radius;
	float discr = b * b - a * c;
	if (discr > 0)
	{
		float temp = (-b - sqrt(discr)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec->t = temp;
			rec->p = trace(r, rec->t);
			rec->normal = divVec3I(subVec3(rec->p, s->center), s->radius);
			//rec->albedo = s->albedo;
			rec->material = s->material;
			return true;
		}

		temp = (-b + sqrt(discr)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec->t = temp;
			rec->p = trace(r, rec->t);
			rec->normal = divVec3I(subVec3(rec->p, s->center), s->radius);
			//rec->albedo = s->albedo;
			rec->material = s->material;
			return true;
		}
	}
	return false;
}

