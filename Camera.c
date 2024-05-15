#include <math.h>

#include "Camera.h"
#include "Utils.h"

//FUCK VSTUDIO
#ifndef _WIN32
	const vec3 vup = (vec3){ ._ = { 0, 1, 0 } };
#else
	#define M_PI 0
	const vec3 vup;
#endif

struct camera newCam(vec3 origin, vec3 destination, vec3 vup, float vfov, float aspect, float aperture, float focusDist)
{
	struct camera cam;
	vec3 u, v, w;

	cam.lensRadius = aperture / 2.0f;

	float theta = vfov * M_PI / 180.0f;
	float halfHeight = tan(theta / 2.0f);
	float halfWidth  = aspect * halfHeight;

	cam.origin = origin;

	w = unit(subVec3(origin, destination));
	u = unit(cross(vup, w));
	v = cross(w, u);

	cam.w = w;

	vec3 uWidth  = mulVec3I(u, focusDist * halfWidth);
	vec3 vHeight = mulVec3I(v, focusDist * halfHeight);
	vec3 wScale  = mulVec3I(w, focusDist);

	//cam.lowerLeftCorner = (vec3){ {-halfWidth, -halfHeight, -1.0} };
	cam.lowerLeftCorner = subVec3(subVec3(subVec3(origin, uWidth),vHeight),wScale);
	cam.u = mulVec3I(uWidth,  2.0f);
	cam.v = mulVec3I(vHeight, 2.0f);

	return cam;
}




ray getRay(struct camera* c, float u, float v)
{
	vec3 rd = mulVec3I(randomInUnitSphere(), c->lensRadius);

	vec3 offset = addVec3(mulVec3I(c->u, rd.x), mulVec3I(c->v, rd.y));

	vec3 uHori = mulVec3I(c->u, u);
	vec3 vVert = mulVec3I(c->v, v);

	vec3 dir = subVec3(subVec3(addVec3(addVec3(uHori, vVert), c->lowerLeftCorner), c->origin), offset);
	ray r = { .origin = addVec3(c->origin, offset), .direction = dir };

	return r;
}
