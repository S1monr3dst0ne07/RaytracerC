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


struct materialReturn lambertian(ray* rIn, struct hitRecord* rec)
{
	struct materialReturn output;

	vec3 rand = randomInUnitSphere();
	vec3 target = addVec3(rec->normal, rand);

	output.scattered = (ray){ .A = addVec3I(rec->p, 0), .B = addVec3I(target, 0) };
	output.atten = rec->albedo;
	output.bounce = true;

	return output;
}


struct materialReturn metal(ray* rIn, struct hitRecord* rec)
{
	struct materialReturn output;

	vec3 unitDir = unit(rIn->B);
	vec3 reflected = reflect(unitDir, rec->normal);

	output.scattered = (ray){ .A = addVec3I(rec->p, 0), .B = reflected };
	output.atten = rec->albedo;
	output.bounce = (dotVec3(output.scattered.B, rec->normal) > 0);

	return output;
}
