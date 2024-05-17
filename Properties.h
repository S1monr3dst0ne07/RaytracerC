#ifndef HPROPERTIES
#define HPROPERTIES

#include "Ray.h"

#include <stdbool.h>

enum materialTypes
{
	LAMBERTIAN = 0,
	METAL,
	DIELECTRIC
};


struct materialProperty
{
	enum materialTypes type;
	vec3 albedo;
	float refIndex;
	float fuzz;
};


struct materialReturn
{
	vec3 atten;
	struct ray scattered;
	bool bounce;

};



#endif