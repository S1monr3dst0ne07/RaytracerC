
#include "Material.h"
#include "Ray.h"


vec3 trace(struct ray* r, float t)
{
	return addVec3(mulVec3I(r->direction, t), r->origin);
}

struct ray getRay(struct camera* c, float u, float v)
{
	vec3 rd = mulVec3I(randomInUnitSphere(), c->lensRadius);

	vec3 offset = addVec3(mulVec3I(c->u, rd.x), mulVec3I(c->v, rd.y));

	vec3 uHori = mulVec3I(c->u, u);
	vec3 vVert = mulVec3I(c->v, v);

	vec3 dir = subVec3(subVec3(addVec3(addVec3(uHori, vVert), c->lowerLeftCorner), c->origin), offset);
	struct ray r = {
		.origin = addVec3(c->origin, offset), 
		.direction = dir,
		.dot = dotVec3(dir, dir)
	};

	return r;
}
