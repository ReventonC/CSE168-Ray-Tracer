////////////////////////////////////////
// MeshObject.h
////////////////////////////////////////

#pragma once

#include "Object.h"
#include "Triangle.h"
#include <vector>

#define vector std::vector

////////////////////////////////////////////////////////////////////////////////

class MeshObject:public Object {
public:
	MeshObject();
	~MeshObject();

	bool Intersect(const Ray &ray,Intersection &hit);

	void MakeBox(float x,float y,float z,Material *mtl=0);

	bool LoadPLY(const char * filename, Material * mtl);

	void Smooth();

	vector<Triangle*> * GetTriangles();

private:
	int NumVertexes,NumTriangles;
	vector<Vertex*> Vertexes;
	vector<Triangle*> Triangles;
};

////////////////////////////////////////////////////////////////////////////////
