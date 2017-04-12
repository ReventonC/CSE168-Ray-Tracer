#pragma once
#include "Object.h"
#include "Material.h"
#include "LambertMaterial.h"
#include "Ray.h"
class SphereObject :public Object
{
public:
	SphereObject();
	~SphereObject();
	void SetRadius(float radius) { rad = radius; }
	void SetCenter(vec pos) { center = pos; }
	bool Intersect(const Ray &ray, Intersection &hit);


private:
	float rad;
	vec center;
	Material *Mtl;
};