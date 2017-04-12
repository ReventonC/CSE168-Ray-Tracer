#include "PlaneObject.h"


PlaneObject::PlaneObject()
{
	Mtl = new LambertMaterial;
	Color col;
	Mtl->SetColor(col.WHITE);
}


PlaneObject::~PlaneObject()
{
}

bool PlaneObject::Intersect(const Ray & ray, Intersection & hit)
{
	vec pos = ray.Origin;
	vec dir = ray.Direction;
	float nDotd = glm::dot(dir, normal);
	if (nDotd != 0) {
		float foo = glm::dot(ray.Origin - center, normal);
		float t = -1 * foo / nDotd;
		if (t > 0) {
			hit.HitDistance = t - 0.001f;
			hit.Position = hit.HitDistance * dir + pos;
			hit.Normal = normal;
			hit.Mtl = Mtl;
			return true;
		}
	}
	return false;
}
