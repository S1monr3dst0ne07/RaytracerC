#ifndef MATERIAL
#define MATERIAL

#include "Sphere.h"

enum materialTypes
{
	LAMBERTIAN = 0,
	METAL
};

struct materialReturn
{
	vec3 atten;
	ray scattered;
	bool bounce;

};


vec3 randomInUnitSphere();
vec3 reflect(vec3 v, vec3 n);
struct materialReturn lambertian(ray* rIn, struct hitRecord* rec);
struct materialReturn metal(ray* rIn, struct hitRecord* rec);


#endif