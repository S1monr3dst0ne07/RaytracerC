#ifndef RAY
#define RAY

#include <stdlib.h>

#include "Vec3.h"
#include "Camera.h"

typedef struct
{
	vec3 origin;
	vec3 direction;

	vec3 direction2;

} ray;


vec3 trace(ray* r, float t);
ray getRay(struct camera* c, float u, float v);

#endif