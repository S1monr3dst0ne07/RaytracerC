
#include "World.h"
#include "Config.h"
#include "Camera.h"
#include "Material.h"

bool worldHit(struct world* w, ray* r, float tMin, float tMax, struct hitRecord* rec)
{
	struct hitRecord tempRec;
	tempRec.normal = nullVec3;
	tempRec.p = nullVec3;

	bool hasHit = false;
	double currentClosest = tMax;

	for (int i = 0; i < w->size; i++)
	{
		if (sphereHit(w->list[i], r, tMin, currentClosest, &tempRec))
		{
			hasHit = true;
			currentClosest = tempRec.t;

			rec->t = tempRec.t;
			//rec->p		= addVec3I(tempRec.p, 0);
			//rec->normal = addVec3I(tempRec.normal, 0);
			rec->p = tempRec.p;
			rec->normal = tempRec.normal;

			rec->material = tempRec.material;

			//rec->albedo = tempRec.albedo;
			//rec->materialType = w->list[i]->materialType;

		}
	}

	return hasHit;
}


vec3 color(ray* r, struct world* w, int depth)
{
	vec3 output = { .x = {0.5f, 0.7f, 1.0f} };
	struct hitRecord rec;
	rec.normal = nullVec3;
	rec.p = nullVec3;
	rec.t = 0;

	if (worldHit(w, r, 0.00001, 10000000.0, &rec))
	{
		struct materialReturn mR;
		mR.bounce = false;
		mR.atten = nullVec3;
		mR.scattered = (ray){ .origin = nullVec3, .direction = nullVec3 };

		switch (rec.material.type)
		{
		case LAMBERTIAN:	mR = lambertian(r, &rec); break;
		case METAL:			mR = metal(r, &rec); break;
		case DIELECTRIC:	mR = dielectric(r, &rec); break;

		}

		if (depth < 50 && mR.bounce)
		{
			vec3 bounceColor = color(&mR.scattered, w, depth + 1);
			output = mulVec3(mR.atten, bounceColor);
		}
	}

	return output;
}





