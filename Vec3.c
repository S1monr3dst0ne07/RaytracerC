#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Vec3.h"


void printVec3(vec3 v)
{
	printf("Vec3(%f, %f, %f)\n", v._[0], v._[1], v._[2]);
}

vec3 vec(float x, float y, float z)
{
	return (vec3) { ._ = { x, y, z } };
}

float length2(vec3 v) { return dotVec3(v, v);    }
float length(vec3 v)  { return sqrt(length2(v)); }
vec3 unit(vec3 v) { return divVec3I(v, length(v)); }

vec3 cross(vec3 v0, vec3 v1)
{
	vec3 out = { ._ = {
		v0._[1] * v1._[2] - v0._[2] * v1._[1],
	  -(v0._[0] * v1._[2] - v0._[2] * v1._[0]),
		v0._[0] * v1._[1] - v0._[1] * v1._[0]
	}};

	return out;
}

