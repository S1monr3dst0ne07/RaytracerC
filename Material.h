#ifndef MATERIAL
#define MATERIAL

#include "Properties.h"
#include "Ray.h"
#include "Sphere.h"



vec3 randomInUnitSphere();
vec3 reflect(vec3 v, vec3 n);
struct materialReturn lambertian(ray* in, struct hitRecord* rec);
struct materialReturn metal(ray* in, struct hitRecord* rec);
struct materialReturn dielectric(ray* in, struct hitRecord* rec);


#endif