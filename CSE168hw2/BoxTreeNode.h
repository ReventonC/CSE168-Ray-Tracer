#pragma once
#include <vector>
#include "Ray.h"
#include "InstanceObject.h"
#include "Triangle.h"

#define vector std::vector

class BoxTreeNode {
public:

	BoxTreeNode();

	~BoxTreeNode();

	bool IntersectBox(const Ray & ray, float &);

	bool Intersect(const Ray &ray, Intersection &hit);

	void Construct(vector<Triangle*> * Tri);

private:

	glm::vec3 BoxMin, BoxMax;

	BoxTreeNode *Child1, *Child2;

	vector<Triangle*> * Tri;
};

