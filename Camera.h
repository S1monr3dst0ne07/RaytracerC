#ifndef CAMERA
#define CAMERA

#include "Vec3.h"
#include "Config.h"

struct camera
{
	vec3 lowerLeftCorner;
	vec3 origin;

	vec3 w;
	vec3 u;
	vec3 v;

	float lensRadius;
};

struct camera newCam(vec3 origin, vec3 destination, vec3 vup, float vfov, float aspect, float aperture, float focusDist);


#endif