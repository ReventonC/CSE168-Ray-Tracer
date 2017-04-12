#pragma once
#include "Object.h"
#include "Material.h"
#include "LambertMaterial.h"
#include "Ray.h"
class PlaneObject :
	public Object
{
public:
	PlaneObject();
	~PlaneObject();
	bool Intersect(const Ray & ray, Intersection & hit);
private:
	vec normal = vec(0, 1, 0);
	vec center = vec(0, 0, 0);
	float distance = 0;
	Material *Mtl;
};

