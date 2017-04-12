#include "SphereObject.h"

SphereObject::SphereObject()
{
	Mtl = new LambertMaterial;
	Color col;
	Mtl->SetColor(col.WHITE);
}


SphereObject::~SphereObject()
{
}


bool SphereObject::Intersect(const Ray & ray, Intersection & hit)
{
	vec pos = ray.Origin;
	vec dir = ray.Direction;

	vec p2c = pos - center;
	float a = 1;
	float b = 2 * dot(p2c, dir);
	float c = dot(p2c, p2c) - rad*rad;
	float dist = b * b - 4 * c;
	if (dist >= 0) {
		float r1 = ((-b - sqrt(dist)) / 2);
		float r2 = ((-b + sqrt(dist)) / 2);
		if (r1 < r2) {
			if (r1 > 0 && r1 < hit.HitDistance || hit.HitDistance < 0) {
				hit.HitDistance = r1 - 0.00001f;
				hit.Position = ray.Origin + r1*dir;
				hit.Normal = glm::normalize(hit.Position - center);
				hit.Mtl = Mtl;
				return true;
			}
			if (r2 > 0 && r2 < hit.HitDistance || hit.HitDistance < 0) {
				hit.HitDistance = r2 - 0.00001f;
				hit.Position = ray.Origin + r2*dir;
				hit.Normal = glm::normalize(hit.Position - center);
				hit.Mtl = Mtl;
				return true;
			}
		}
		else {
			if (r2 > 0 && r2 < hit.HitDistance || hit.HitDistance < 0) {
				hit.HitDistance = r2 - 0.00001f;
				hit.Position = ray.Origin + r2*dir;
				hit.Normal = glm::normalize(hit.Position - center);
				hit.Mtl = Mtl;
				return true;
			}
			if (r1 > 0 && r1 < hit.HitDistance || hit.HitDistance < 0) {
				hit.HitDistance = r1 - 0.00001f;
				hit.Position = ray.Origin + r1*dir;
				hit.Normal = glm::normalize(hit.Position - center);
				hit.Mtl = Mtl;
				return true;
			}
		}
	}
	return false;
}
