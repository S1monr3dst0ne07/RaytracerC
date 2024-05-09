#include <math.h>

#include "Camera.h"

//FUCK VSTUDIO
#ifndef _WIN32
	const vec3 vup = (vec3){ .x = { 0, 1, 0 } };
#else
	#define M_PI 0
	const vec3 vup;
#endif

struct camera newCam(vec3 origin, vec3 destination, vec3 vup, float vfov, float aspect)
{
	struct camera cam;
	vec3 u, v, w;

	float theta = vfov * M_PI / 180.0f;
	float halfHeight = tan(theta / 2.0f);
	float halfWidth  = aspect * halfHeight;

	cam.origin = origin;

	w = unit(subVec3(origin, destination));
	u = unit(cross(vup, w));
	v = cross(w, u);

	cam.w = w;

	vec3 uWidth  = mulVec3I(u, halfWidth);
	vec3 vHeight = mulVec3I(v, halfHeight);

	//cam.lowerLeftCorner = (vec3){ {-halfWidth, -halfHeight, -1.0} };
	cam.lowerLeftCorner = subVec3(subVec3(subVec3(origin, uWidth),vHeight),w);
	cam.hori = mulVec3I(uWidth,  2.0f);
	cam.vert = mulVec3I(vHeight, 2.0f);

	return cam;
}





ray getRay(struct camera* c, float u, float v)
{
	vec3 uHori = mulVec3I(c->hori, u);
	vec3 vVert = mulVec3I(c->vert, v);

	vec3 dir = subVec3(addVec3(addVec3(uHori, vVert), c->lowerLeftCorner), c->origin);
	ray r = { .origin = c->origin, .direction = dir };

	return r;
}
