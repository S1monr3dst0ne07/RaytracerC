#ifndef VEC3
#define VEC3

typedef struct
{
	union
	{
		struct { float x, y, z; };
		float _[3];
	};
} vec3;

#define nullVec3 ((vec3){ ._ = {0, 0, 0} })
#define fillVec3(y) ((vec3){ ._ = {y, y, y} })


void printVec3(vec3 v);
vec3 vec(float x, float y, float z);

#define nullVec3 ((vec3){ ._ = {0, 0, 0} })
#define fillVec3(y) ((vec3){ ._ = {y, y, y} })

//inline vec3 addVec3(vec3 v0, vec3 v1);
//inline vec3 subVec3(vec3 v0, vec3 v1);
//inline vec3 mulVec3(vec3 v0, vec3 v1);
//inline vec3 divVec3(vec3 v0, vec3 v1);

inline vec3 addVec3(vec3 v0, vec3 v1) { return (vec3) { ._ = { v0._[0] + v1._[0], v0._[1] + v1._[1], v0._[2] + v1._[2], } }; }
inline vec3 subVec3(vec3 v0, vec3 v1) { return (vec3) { ._ = { v0._[0] - v1._[0], v0._[1] - v1._[1], v0._[2] - v1._[2], } }; }
inline vec3 mulVec3(vec3 v0, vec3 v1) { return (vec3) { ._ = { v0._[0] * v1._[0], v0._[1] * v1._[1], v0._[2] * v1._[2], } }; }
inline vec3 divVec3(vec3 v0, vec3 v1) { return (vec3) { ._ = { v0._[0] / v1._[0], v0._[1] / v1._[1], v0._[2] / v1._[2], } }; }

//inline float dotVec3(vec3 v0, vec3 v1);
inline float dotVec3(vec3 v0, vec3 v1)
{
	return v0._[0] * v1._[0] + v0._[1] * v1._[1] + v0._[2] * v1._[2];
}



#define addVec3I(v0, v1) addVec3(v0, fillVec3(v1))
#define subVec3I(v0, v1) subVec3(v0, fillVec3(v1))
#define mulVec3I(v0, v1) mulVec3(v0, fillVec3(v1))
#define divVec3I(v0, v1) divVec3(v0, fillVec3(v1))



float length(vec3 v);
float length2(vec3 v);
vec3  unit(vec3 v);

vec3 cross(vec3 v0, vec3 v1);

#endif