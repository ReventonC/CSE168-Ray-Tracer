#include "InstanceObject.h"


InstanceObject::InstanceObject()
{
}


InstanceObject::~InstanceObject()
{
}

InstanceObject::InstanceObject(Object & obj)
{
	Child = &obj;
}

bool InstanceObject::Intersect(const Ray & ray, Intersection & hit)
{
	Ray ray2;
	ray2.Origin = glm::vec3(Inverse * glm::vec4(ray.Origin, 1));
	ray2.Direction = glm::vec3(Inverse * glm::vec4(ray.Direction, 0));

	if (Child->Intersect(ray2, hit) == false) return false;

	hit.Position = glm::vec3(Matrix * glm::vec4(hit.Position, 1));
	hit.Normal = glm::normalize(glm::vec3(Matrix * glm::vec4(hit.Normal, 0)));
	hit.Mtl = mtl;
	return true;

}

void InstanceObject::SetChild(Object & obj)
{
	Child = &obj;
}

void InstanceObject::SetMatrix(glm::mat4x4 & mtx)
{
	Matrix = mtx;
	Inverse = glm::inverse(mtx);
}

void InstanceObject::SetMaterial(Material * m)
{
	mtl = m;
}

