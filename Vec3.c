#include "Vec3.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
/*
vec3* newVec3(float d0, float d1, float d2)
{
	vec3* out = (vec3*)malloc(sizeof(vec3));
	out->x[0] = d0;
	out->x[1] = d1;
	out->x[2] = d2;

	return out;
}*/

void printVec3(vec3 v)
{
	printf("Vec3(%f, %f, %f)\n", v.x[0], v.x[1], v.x[2]);
}

/*vec3 nullVec3()
{
	vec3 null = { .x = {0, 0, 0} };
	return null;
}*/


/*vec3 fillVec3(float x)
{
	vec3 out;
	for (int i = 0; i < 3; i++)
		out.x[i] = x;
	return out;
}*/

vec3 addVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] + v1.x[0], v0.x[1] + v1.x[1], v0.x[2] + v1.x[2], } }; }
vec3 subVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] - v1.x[0], v0.x[1] - v1.x[1], v0.x[2] - v1.x[2], } }; }
vec3 mulVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] * v1.x[0], v0.x[1] * v1.x[1], v0.x[2] * v1.x[2], } }; }
vec3 divVec3(vec3 v0, vec3 v1) { return (vec3) { .x = { v0.x[0] / v1.x[0], v0.x[1] / v1.x[1], v0.x[2] / v1.x[2], } }; }

//vec3 addVec3I(vec3 v0, float v1) { return addVec3(v0, fillVec3(v1)); }
//vec3 subVec3I(vec3 v0, float v1) { return subVec3(v0, fillVec3(v1)); }
//vec3 mulVec3I(vec3 v0, float v1) { return mulVec3(v0, fillVec3(v1)); }
//vec3 divVec3I(vec3 v0, float v1) { return divVec3(v0, fillVec3(v1)); }

//sums all components of a vec3
/*inline float sumVec3(vec3 v)
{
	return	v.x[0] + v.x[1] + v.x[2];
}*/

//float dotVec3(vec3 v0, vec3 v1) { return sumVec3(mulVec3(v0, v1)); }
float dotVec3(vec3 v0, vec3 v1)
{
	return v0.x[0] * v1.x[0] + v0.x[1] * v1.x[1] + v0.x[2] * v1.x[2];
}

float length2(vec3 v) { return dotVec3(v, v); }
//define length2(v) dotVec3(v, v)
float length(vec3 v) { return sqrt(length2(v)); }
//define length(v) sqrt(length2(v))
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