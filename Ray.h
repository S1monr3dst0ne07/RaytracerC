#ifndef RAY
#define RAY

#include <stdlib.h>
#include "Vec3.h"

typedef struct
{
	vec3 A;
	vec3 B;

} ray;


//ray* newRay(vec3 A, vec3 B);

vec3 pap(ray* r, float t);

#endif