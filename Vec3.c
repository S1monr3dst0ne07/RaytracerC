#include "Vec3.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


void printVec3(vec3 v)
{
	printf("Vec3(%f, %f, %f)\n", v.x[0], v.x[1], v.x[2]);
}

vec3 vec(float x, float y, float z)
{
	return (vec3) { .x = { x, y, z } };
}


vec3 addVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] + v1.x[0], v0.x[1] + v1.x[1], v0.x[2] + v1.x[2], } }; }
vec3 subVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] - v1.x[0], v0.x[1] - v1.x[1], v0.x[2] - v1.x[2], } }; }
vec3 mulVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] * v1.x[0], v0.x[1] * v1.x[1], v0.x[2] * v1.x[2], } }; }
vec3 divVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] / v1.x[0], v0.x[1] / v1.x[1], v0.x[2] / v1.x[2], } }; }

float dotVec3(vec3 v0, vec3 v1)
{
	return v0.x[0] * v1.x[0] + v0.x[1] * v1.x[1] + v0.x[2] * v1.x[2];
}

float length2(vec3 v) { return dotVec3(v, v);    }
float length(vec3 v)  { return sqrt(length2(v)); }
vec3 unit(vec3 v) { return divVec3I(v, length(v)); }

vec3 cross(vec3 v0, vec3 v1)
{
	vec3 out = { .x = {
		v0.x[1] * v1.x[2] - v0.x[2] * v1.x[1],
	  -(v0.x[0] * v1.x[2] - v0.x[2] * v1.x[0]),
		v0.x[0] * v1.x[1] - v0.x[1] * v1.x[0]
	}};

	return out;
}