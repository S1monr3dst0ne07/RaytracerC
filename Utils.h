#ifndef HUTILS
#define HUTILS

#include "Vec3.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>



float randTot1()
{
	return drand48() * 2 - 1;
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