#ifndef MATERIAL
#define MATERIAL

#include "Properties.h"
#include "Ray.h"
#include "Sphere.h"



vec3 randomInUnitSphere();
vec3 reflect(vec3 v, vec3 n);
struct materialReturn lambertian(struct ray* in, struct hitRecord* rec);
struct materialReturn metal(struct ray* in, struct hitRecord* rec);
struct materialReturn dielectric(struct ray* in, struct hitRecord* rec);


#endif