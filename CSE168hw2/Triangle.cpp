#include "Triangle.h"
#include <iostream>
Triangle::Triangle()
{
}

void Triangle::Init(Vertex * v0, Vertex * v1, Vertex * v2, Material * m)
{
	Vtx[0] = v0; Vtx[1] = v1; Vtx[2] = v2; Mtl = m;
}

bool Triangle::Intersect(const Ray & ray, Intersection & hit) const
{
	vec pos = ray.Origin;
	vec dir = glm::normalize(ray.Direction);

	vec v1 = Vtx[0]->Position;
	vec v2 = Vtx[1]->Position;
	vec v3 = Vtx[2]->Position;

	vec normal;
	vec A = v2 - v1;
	vec B = v3 - v1;
	vec C = glm::cross(A, B);
	normal = glm::normalize(C);

	float D = -dot(normal, v1);
	float t = -(dot(normal, pos) + D) / dot(normal, dir);

	vec P = pos + (float)t * dir;

	vec e1 = v2 - v1;
	vec e2 = v3 - v2;
	vec e3 = v1 - v3;
	vec c1 = P - v1;
	vec c2 = P - v2;
	vec c3 = P - v3;

	if (dot(normal, cross(e1, c1)) >= 0 &&
		dot(normal, cross(e2, c2)) >= 0 &&
		dot(normal, cross(e3, c3)) >= 0) {

		if (t > 0 && t < hit.HitDistance) {
			hit.HitDistance = t - 0.00001f;
			hit.Position = pos + hit.HitDistance * ray.Direction;
			hit.Normal = glm::normalize(normal);
			hit.Mtl = Mtl;
			return true;
		}
	}
	return false;
}

Vertex Triangle::GetVtx(int num)
{
	Vertex ret;
	ret.Normal = Vtx[num]->Normal;
	ret.Position = Vtx[num]->Position;
	ret.TexCoord = Vtx[num]->TexCoord;
	return ret;
}
