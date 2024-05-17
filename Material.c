
#include <stdio.h>

#include "Vec3.h"
#include "Material.h"




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

float schlick(float cosine, float refIndex)
{
	float r0 = (1.0f - refIndex) / (1.0f + refIndex);
	float r1 = r0 * r0;
	return r1 + (1.0f - r1) * pow((1.0f - cosine), 5);
}


struct materialReturn lambertian(ray* in, struct hitRecord* rec)
{
	struct materialReturn output;

	vec3 rand = mulVec3I(randomInUnitSphere(), rec->material.fuzz);
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

	vec3 reflected = reflect(in->direction, rec->normal);
	vec3 refracted;

	//output.atten = vec(1.0, 1.0, 1.0);
	output.atten = rec->material.albedo;

	float refDot = dotVec3(in->direction, rec->normal);
	bool isReflect = refDot > 0;
	vec3  outwordNormal = isReflect ? subVec3(nullVec3, rec->normal) : rec->normal;
	float indexRatio    = isReflect ? refIndex : 1.0f / refIndex;
	float cosine        = isReflect ? 
		refIndex * refDot / length(in->direction) :
		          -refDot / length(in->direction) ;

	//schlick(cosine, refIndex)
	bool isRefract = refract(in->direction, outwordNormal, indexRatio, &refracted);
	float reflectProb = isRefract ? schlick(cosine, refIndex) : 1.0f;

	output.scattered = (ray){
		.origin = rec->p,
		.direction = drand48() < reflectProb ? reflected : refracted
	};

	output.bounce = true;

	return output;
}
