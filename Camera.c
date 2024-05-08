#include "Camera.h"

#ifndef _WIN32
	const vec3 vup = (vec3){ .x = { 0, 1, 0 } };
#else
	const vec3 vup;
#endif

struct camera newCam(vec3 origin, vec3 destination)
{
	vec3 delta = subVec3(origin, destination);
	float focalLength = length(delta);

	vec3 w = unit(delta);
	vec3 u = unit(cross(vup, w));
	vec3 v = cross(w, u);

	int width = 4.0f;
	int height = 2.0f;

	vec3 uPort = mulVec3I(u, width);
	vec3 vPort = mulVec3I(v, height);

	vec3 upperLeftCorner = 
		subVec3(
			origin, 
			addVec3(
				addVec3(
					mulVec3I(w, focalLength), 
					divVec3I(uPort, 2.0f)), 
				divVec3I(vPort, 2.0f)
			)
		);

	struct camera cam = {
		.lowerLeftCorner = upperLeftCorner,
		.hori			 = uPort,
		.vert		     = vPort,
		.origin			 = origin
	};

	return cam;
}





ray getRay(struct camera* c, float u, float v)
{
	vec3 uHori = mulVec3I(c->hori, u);
	vec3 vVert = mulVec3I(c->vert, v);

	vec3 dir = addVec3(addVec3(uHori, vVert), c->lowerLeftCorner);
	ray r = { .A = c->origin, .B = dir };

	return r;
}
