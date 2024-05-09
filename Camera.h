#ifndef CAMERA
#define CAMERA

#include "Ray.h"
#include "Config.h"

struct camera
{
	vec3 lowerLeftCorner;
	vec3 hori;
	vec3 vert;
	vec3 origin;

	vec3 w;
};

struct camera newCam(vec3 origin, vec3 destination, vec3 vup, float vfov, float aspect);
ray getRay(struct camera* c, float u, float v);


#endif