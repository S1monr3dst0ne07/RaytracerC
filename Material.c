#include "Vec3.h"

#include <stdio.h>
#include "Material.h"

float randAbs1()
{
	return rand() / (float)RAND_MAX;
}

float randTot1()
{
	return randAbs1() * 2 - 1;
}

vec3 randomInUnitSphere()
{
	vec3 p = nullVec3;
	do
	{
		p = (vec3){.x = {
			randTot1(),
			randTot1(),
			randTot1(),
		}};

	} while (length(p) >= 1.0 && false);
	return p;
}



vec3 reflect(vec3 v, vec3 n)
{
	return subVec3(v, mulVec3I(n, 2 * dotVec3(v, n)));
}

bool refract(vec3 v, vec3 n, float indexRatio, vec3* refracted)
{
	vec3 uv = unit(v);
	float dt = dotVec3(uv, n);
	float discr = 1.0f - indexRatio * indexRatio * (1.0f - dt * dt);

	bool refract = discr > 0.0f;
	if (refract) *refracted = subVec3(
		mulVec3I(subVec3(uv, mulVec3I(n, dt)), indexRatio),
		mulVec3I(n, sqrt(discr))
	);

	return refract;
}


struct materialReturn lambertian(ray* in, struct hitRecord* rec)
{
	struct materialReturn output;

	vec3 rand = randomInUnitSphere();
	vec3 target = addVec3(rec->normal, rand);

	output.scattered = (ray){ 
		.origin    = addVec3I(rec->p, 0), 
		.direction = addVec3I(target, 0)
	};
	output.atten = rec->material.albedo;
	output.bounce = true;

	return output;
}


struct materialReturn metal(ray* in, struct hitRecord* rec)
{
	struct materialReturn output;

	float fuzz = rec->material.fuzz;

	vec3 unitDir = unit(in->direction);
	vec3 reflected = reflect(unitDir, rec->normal);

	output.scattered = (ray){
		.origin = rec->p,
		.direction = addVec3(reflected, mulVec3I(randomInUnitSphere(), fuzz))
	};
	output.atten = rec->material.albedo;
	output.bounce = (dotVec3(output.scattered.direction, rec->normal) > 0);

	return output;
}


struct materialReturn dielectric(ray* in, struct hitRecord* rec)
{
	struct materialReturn output;

	float refIndex = rec->material.refIndex;

	vec3 outwordNormal;
	vec3 reflected = reflect(in->direction, rec->normal);
	float indexRatio;

	vec3 refracted;

	output.atten = (vec3){ { 1.0, 1.0, 1.0 } };

	bool isReflect = dotVec3(in->direction, rec->normal) > 0;
	outwordNormal = isReflect ? subVec3(nullVec3, rec->normal) : rec->normal;
	indexRatio    = isReflect ? refIndex : 1.0f / refIndex;

	bool isRefract = refract(in->direction, outwordNormal, indexRatio, &refracted);
	output.scattered = (ray){
		.origin = rec->p,
		.direction = isRefract ? refracted : reflected
	};

	return output;
}
