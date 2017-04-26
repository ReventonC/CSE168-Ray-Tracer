#pragma once
#include "BoxTreeNode.h"
#include "Object.h"
#include "MeshObject.h"
class BoxTreeObject :
	public Object
{
public:

	BoxTreeObject();

	~BoxTreeObject();

	bool Intersect(const Ray &ray, Intersection &hit);

	void Construct(MeshObject &mesh);

private:

	BoxTreeNode *RootNode;
};

