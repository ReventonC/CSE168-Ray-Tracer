#include "BoxTreeObject.h"


BoxTreeObject::BoxTreeObject()
{
}


bool BoxTreeObject::Intersect(const Ray & ray, Intersection & hit)
{
	float t = 0;
	if (RootNode->IntersectBox(ray, t)) return RootNode->Intersect(ray, hit);
	return false;
}

void BoxTreeObject::Construct(MeshObject & mesh)
{
 	RootNode = new BoxTreeNode();
	vector<Triangle*> * Tris = mesh.GetTriangles();
	RootNode->Construct(Tris);
}

BoxTreeObject::~BoxTreeObject()
{
}
