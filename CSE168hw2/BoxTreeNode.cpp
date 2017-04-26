#include "BoxTreeNode.h"


BoxTreeNode::BoxTreeNode()
{
	this->Tri = new vector<Triangle *>;
}


BoxTreeNode::~BoxTreeNode()
{
}

// helper funcs
float min(float a, float b) 
{
	return a < b ? a : b;
}

float max(float a, float b)
{
	return a > b ? a : b;
}

float min(float a, float b, float c)
{
	float d = a < b ? a : b;
	return c < d ? c : d;
}

float max(float a, float b, float c)
{
	float d = a > b ? a : b;
	return c > d ? c : d;
}

bool BoxTreeNode::IntersectBox(const Ray & ray, float & t)
{
	float tx1 = (BoxMin.x - ray.Origin.x) / ray.Direction.x;
	float tx2 = (BoxMax.x - ray.Origin.x) / ray.Direction.x;
	float ty1 = (BoxMin.y - ray.Origin.y) / ray.Direction.y;
	float ty2 = (BoxMax.y - ray.Origin.y) / ray.Direction.y;
	float tz1 = (BoxMin.z - ray.Origin.z) / ray.Direction.z;
	float tz2 = (BoxMax.z - ray.Origin.z) / ray.Direction.z;
	float tmin = max(min(tx1, tx2), min(ty1, ty2), min(tz1, tz2));
	float tmax = min(max(tx1, tx2), max(ty1, ty2), max(tz1, tz2));
	if (tmin > 0 && tmin <= tmax) {
		t = tmin;
		return true;
	}
	if (tmin < 0 && tmax > 0) {
		t = tmax;
		return true;
	}
	return false;
}

bool BoxTreeNode::Intersect(const Ray & ray, Intersection & hit)
{
	if (Tri->size() > 0) {
		bool success = false;
		for (auto Atri : *Tri) {
			if (Atri->Intersect(ray, hit)) success = true;
		}
		return success;
	}

	//Test childs
	float dist1 = 1e10, dist2 = 1e10;
	bool c1 = Child1->IntersectBox(ray, dist1);
	bool c2 = Child2->IntersectBox(ray, dist2);

	if (!c1 && !c2) {
		return false;
	}

	bool success = false;
	if (dist1 < dist2) {
		if (c1 && dist1 < hit.HitDistance) {
			if (Child1->Intersect(ray, hit)) success = true;
		}
		if (c2 && dist2 < hit.HitDistance) {
			if (Child2->Intersect(ray, hit)) success = true;
		}
	}
	else {
		if (c2 && dist2 < hit.HitDistance) {
			if (Child2->Intersect(ray, hit)) success = true;
		}
		if (c1 && dist1 < hit.HitDistance) {
			if (Child1->Intersect(ray, hit)) success = true;
		}
	}
	return success;
}

int findSplit(vec min, vec max) {
	vec diff = max - min;
	//x = 0
	if (diff.x > diff.y && diff.x > diff.z) {
		return 0;
	}
	//y = 1
	if (diff.y > diff.x && diff.y > diff.z) {
		return 1;
	}
	//z = 2
	return 2;
}

void BoxTreeNode::Construct(vector<Triangle*> *Tri)
{
	//std::cout << Tri->size() << std::endl;
	// Compute BoxMin & BoxMax to fit around all tri
	BoxMin = Tri->front()->GetVtx(0).Position;
	BoxMax = Tri->front()->GetVtx(0).Position;
	for (auto Atri : *Tri) {
		for (int i = 0; i < 3; i++) {
			if (BoxMin.x > Atri->GetVtx(i).Position.x) BoxMin.x = Atri->GetVtx(i).Position.x;
			if (BoxMin.y > Atri->GetVtx(i).Position.y) BoxMin.y = Atri->GetVtx(i).Position.y;
			if (BoxMin.z > Atri->GetVtx(i).Position.z) BoxMin.z = Atri->GetVtx(i).Position.z;

			if (BoxMax.x < Atri->GetVtx(i).Position.x) BoxMax.x = Atri->GetVtx(i).Position.x;
			if (BoxMax.y < Atri->GetVtx(i).Position.y) BoxMax.y = Atri->GetVtx(i).Position.y;
			if (BoxMax.z < Atri->GetVtx(i).Position.z) BoxMax.z = Atri->GetVtx(i).Position.z;
		}
	}

	// Check if this is a leaf node
	if (Tri->size() <= 10) {	
		// Copy triangles to BoxTreeNode Tri array
		for (size_t i = 0; i < Tri->size(); i ++) {
			this->Tri->push_back(Tri->at(i));
		}
		return;
	}

	// Determine largest box dimension x, y, or z
	// Compute splitting plane halfway along largest dimension
	// Allocate two new temporary arrays
	int half = findSplit(BoxMin, BoxMax);
	vec mid = (BoxMin + BoxMax) / 2.f;

	// Place triangles into group 1 or group 2
	vector<Triangle *> tri1, tri2;
	for (auto Atri: *Tri) {
		// Compute center of triangle & determine which side of splitting plane
		// Add to appropriate group
		vec triMid = vec(Atri->GetVtx(0).Position + Atri->GetVtx(1).Position + Atri->GetVtx(2).Position) / 3.0f;

		if (half == 0) {
			if (triMid.x > mid.x) tri1.push_back(Atri); else tri2.push_back(Atri);
		}
		else if (half == 1) {
			if (triMid.y > mid.y) tri1.push_back(Atri); else tri2.push_back(Atri);
		}
		else {
			if (triMid.z > mid.z) tri1.push_back(Atri); else tri2.push_back(Atri);
		}
	}
	// Check if either group is empty. If so, move (at least) 1 triangle into that group
	// Recursively build sub-trees
	if (tri1.size() == 0) {
		tri1.push_back(tri2.back());
		tri2.pop_back();
	} else if (tri2.size() == 0) {
		tri2.push_back(tri1.back());
		tri1.pop_back();
	}
	Child1 = new BoxTreeNode; Child2 = new BoxTreeNode;
	Child1->Construct(&tri1); 
	Child2->Construct(&tri2);
}
