
#include <string.h>

#include "World.h"
#include "Config.h"
#include "Camera.h"
#include "Material.h"




struct world newDemoWorld()
{

	int listSize = sizeof(struct sphere*) * 1024;

	struct sphere** spheres = malloc(listSize);
	memset(spheres, 0x0, listSize);

	struct world w = {
		.list = spheres,
		.size = 0
	};

	spheres[w.size++] = newSphere(vec( 0,  0,     0), 0.5, (struct materialProperty) { .type = LAMBERTIAN, .albedo = (vec3){ ._ = {0.8, 0.3, 0.3} }, .fuzz     = 1.0f });
	spheres[w.size++] = newSphere(vec( 0, -100.5, 0), 100, (struct materialProperty) { .type = LAMBERTIAN, .albedo = (vec3){ ._ = {0.5, 0.5, 0.5} }, .fuzz     = 0.1f });
	spheres[w.size++] = newSphere(vec( 1,  0,     0), 0.5, (struct materialProperty) { .type = DIELECTRIC, .albedo = (vec3){ ._ = {0.8, 0.6, 0.2} }, .refIndex = 1.5 });
	spheres[w.size++] = newSphere(vec(-1,  0,     0), 0.5, (struct materialProperty) { .type = METAL,      .albedo = (vec3){ ._ = {0.8, 0.8, 0.0} }, .fuzz     = 0.05f });

	//camera
	spheres[w.size++] = newSphere(
		nullVec3,
		0.5, 
		(struct materialProperty) {
			.type = METAL, .albedo = vec(0.1, 0.1, 0.1), .fuzz = 0.7
		}
	);
	spheres[w.size - 1]->isCamera = true;

	return w;
}


void updateCameraSphere(struct world* w, struct camera cam)
{
	vec3 camPos = addVec3(cam.origin, mulVec3I(cam.w, 0.55));

	for (int i = 0; i < w->size; i++)
		if (w->list[i]->isCamera)
			w->list[i]->center = camPos;
}



#define rLAM (drand48() * drand48())
#define rMET (0.5 * (1 + drand48()))


void addRandomSpheres(struct world* w)
{


	for (int a = -11; a < 11; a++)
	for (int b = -11; b < 11; b++)
	{
		float chooseMaterial = drand48();
		vec3 center = vec(a+0.9*drand48(), 0.2, b+0.9*drand48());
		if (length(subVec3(center, vec(4, 0.2, 0))) <= 0.9) continue;

		if (chooseMaterial < 0.8) //diffuse
			w->list[w->size++] = newSphere(center, 0.2, (struct materialProperty) {
				.type = LAMBERTIAN,
				.albedo = vec(rLAM, rLAM, rLAM),
				.fuzz = 0.0f
			});
		else if (chooseMaterial < 0.96) //metal
			w->list[w->size++] = newSphere(center, 0.2, (struct materialProperty) {
				.type = METAL,
				.albedo = vec(rMET, rMET, rMET),
				.fuzz = 0.5f * drand48()
			});
		else
			w->list[w->size++] = newSphere(center, 0.2, (struct materialProperty) {
				.type = DIELECTRIC,
				.albedo = vec(drand48(), drand48(), drand48()),
				.refIndex = 1.5f
			});


	}

}




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
	vec3 output = vec(0.5f, 0.7f, 1.0f);
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





