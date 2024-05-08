#ifndef VEC3
#define VEC3

typedef struct
{
	float x[3];
} vec3;

void printVec3(vec3 v);
//vec3* newVec3(float v0, float v1, float v2);
//vec3 nullVec3();

#define nullVec3 ((vec3){ .x = {0, 0, 0} })
#define fillVec3(y) ((vec3){ .x = {y, y, y} })

//arith
vec3 addVec3(vec3 v0, vec3 v1);
vec3 subVec3(vec3 v0, vec3 v1);
vec3 mulVec3(vec3 v0, vec3 v1);
vec3 divVec3(vec3 v0, vec3 v1);

//vec3 addVec3I(vec3 v0, float v1);
//vec3 subVec3I(vec3 v0, float v1);
//vec3 mulVec3I(vec3 v0, float v1);
//vec3 divVec3I(vec3 v0, float v1);
#define addVec3I(v0, v1) addVec3(v0, fillVec3(v1))
#define subVec3I(v0, v1) subVec3(v0, fillVec3(v1))
#define mulVec3I(v0, v1) mulVec3(v0, fillVec3(v1))
#define divVec3I(v0, v1) divVec3(v0, fillVec3(v1))


//float sumVec3(vec3 v);
//#define sumVec3(v) (v.x[0] + v.x[1] + v.x[2])
float dotVec3(vec3 v0, vec3 v1);

float length(vec3 v);
float length2(vec3 v);
vec3  unit(vec3 v);

vec3 cross(vec3 v0, vec3 v1);

#endif