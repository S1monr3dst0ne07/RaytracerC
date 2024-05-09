#include "Ray.h"
#include "Material.h"


vec3 pap(ray* r, float t)
{
	return addVec3(mulVec3I(r->direction, t), r->origin);
}

