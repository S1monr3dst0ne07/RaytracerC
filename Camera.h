#ifndef CAMERA
#define CAMERA

#include "Ray.h"

struct camera
{
	vec3 lowerLeftCorner;
	vec3 hori;
	vec3 vert;
	vec3 origin;




};

struct camera newCamByBasis(vec3 origin, vec3 u, vec3 v, float h);
struct camera newCam(vec3 origin, vec3 dir);
ray getRay(struct camera* c, float u, float v);


#endif