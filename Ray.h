#ifndef RAY
#define RAY

#include <stdlib.h>
#include "Vec3.h"

typedef struct
{
	vec3 origin;
	vec3 direction;

} ray;


vec3 pap(ray* r, float t);

#endif