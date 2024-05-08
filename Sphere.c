#include "Sphere.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>




bool sphereHit(struct sphere* s, ray* r, float tMin, float tMax, struct hitRecord* rec)
{
	vec3 oc = subVec3(r->A, s->center);
	float a = dotVec3(r->B, r->B);
	float b = dotVec3(oc, r->B);
	float c = dotVec3(oc, oc) - s->radius * s->radius;
	float discr = b * b - a * c;
	if (discr > 0)
	{
		float temp = (-b - sqrt(discr)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec->t = temp;
			rec->p = pap(r, rec->t);
			rec->normal = divVec3I(subVec3(rec->p, s->center), s->radius);
			rec->albedo = s->albedo;
			return true;
		}

		temp = (-b + sqrt(discr)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec->t = temp;
			rec->p = pap(r, rec->t);
			rec->normal = divVec3I(subVec3(rec->p, s->center), s->radius);
			rec->albedo = s->albedo;
			return true;
		}
	}
	return false;
}



bool worldHit(struct world* w, ray* r, float tMin, float tMax, struct hitRecord* rec)
{
	struct hitRecord tempRec;
	tempRec.normal = nullVec3;
	tempRec.p      = nullVec3;

	bool hasHit = false;
	double currentClosest = tMax;

	for (int i = 0; i < w->size; i++)
	{
		if (sphereHit(w->list[i], r, tMin, currentClosest, &tempRec))
		{
			hasHit = true;
			currentClosest = tempRec.t;

			rec->t		= tempRec.t;
			//rec->p		= addVec3I(tempRec.p, 0);
			//rec->normal = addVec3I(tempRec.normal, 0);
			rec->p      = tempRec.p;
			rec->normal = tempRec.normal;
			rec->albedo = tempRec.albedo;
			rec->materialType = w->list[i]->materialType;

		}
	}

	return hasHit;
}