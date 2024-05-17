#ifndef RAY
#define RAY

#include <stdlib.h>

#include "Vec3.h"
#include "Camera.h"

struct ray
{
	vec3 origin;
	vec3 direction;

	float dot;

};


vec3 trace(struct ray* r, float t);
struct ray getRay(struct camera* c, float u, float v);

#endif