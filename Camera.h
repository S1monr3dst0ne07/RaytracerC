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

ray getRay(struct camera* c, float u, float v);


#endif