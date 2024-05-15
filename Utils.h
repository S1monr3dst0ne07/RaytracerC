#ifndef HUTILS
#define HUTILS

#include "Vec3.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

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
		p = fillVec3(randTot1());			
	while (length(p) >= 1.0);

	return p;
}


#endif