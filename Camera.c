#include "Camera.h"

ray getRay(struct camera* c, float u, float v)
{
	vec3 uHori = mulVec3I(c->hori, u);
	vec3 vVert = mulVec3I(c->vert, v);

	vec3 dir = addVec3(addVec3(uHori, vVert), c->lowerLeftCorner);
	ray r = { .A = c->origin, .B = dir };

	return r;
}
