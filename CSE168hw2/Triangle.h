////////////////////////////////////////
// Triangle.h
////////////////////////////////////////

#pragma once

#include "Vertex.h"
#include "Material.h"
#include "LambertMaterial.h"
#include "Ray.h"

#define vec glm::vec3

////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
	Triangle();
	void Init(Vertex *v0, Vertex *v1, Vertex *v2, Material *m);

	//vec getNormal(const vec p) const;
	bool Intersect(const Ray &ray, Intersection &hit) const;

private:
	Vertex *Vtx[3];
	Material *Mtl;
};

////////////////////////////////////////////////////////////////////////////////
