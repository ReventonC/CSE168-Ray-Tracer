////////////////////////////////////////
// MeshObject.cpp
////////////////////////////////////////

#include "MeshObject.h"
#include "LambertMaterial.h"
#include "glm/glm.hpp"

////////////////////////////////////////////////////////////////////////////////

MeshObject::MeshObject() {
	NumVertexes=0;
	NumTriangles=0;
}

////////////////////////////////////////////////////////////////////////////////

MeshObject::~MeshObject() {
}

////////////////////////////////////////////////////////////////////////////////

bool MeshObject::Intersect(const Ray &ray, Intersection &hit) {
	bool success=false;
	for (int i = 0; i < NumTriangles; i++) {
		if(Triangles[i]->Intersect(ray,hit)) success=true;
	}
	return success;
}

////////////////////////////////////////////////////////////////////////////////

void MeshObject::MakeBox(float x,float y,float z,Material *mtl) {
	// Allocate arrays
	NumVertexes=24;
	NumTriangles=12;
	if(mtl==0) mtl=new LambertMaterial;
	Color col;
	mtl->SetColor(col.WHITE);
	x*=0.5f;
	y*=0.5f;
	z*=0.5f;

	// Corners
	glm::vec3 p000(-x,-y,-z);
	glm::vec3 p001(-x,-y,z);
	glm::vec3 p010(-x,y,-z);
	glm::vec3 p011(-x,y,z);
	glm::vec3 p100(x,-y,-z);
	glm::vec3 p101(x,-y,z);
	glm::vec3 p110(x,y,-z);
	glm::vec3 p111(x,y,z);

	// Tex coords
	glm::vec3 t00(0.0f,0.0f,0.0f);
	glm::vec3 t01(0.0f,1.0f,0.0f);
	glm::vec3 t10(1.0f,0.0f,0.0f);
	glm::vec3 t11(1.0f,1.0f,0.0f);

	// Axis vectors
	glm::vec3 xAxis(1,0,0);
	glm::vec3 yAxis(0,1,0);
	glm::vec3 zAxis(0,0,1);

	// Right
	Vertexes.push_back(new Vertex());
	Vertexes[0]->Set(p101,xAxis,t00);
	Vertexes.push_back(new Vertex());
	Vertexes[1]->Set(p100,xAxis,t10);
	Vertexes.push_back(new Vertex());
	Vertexes[2]->Set(p110,xAxis,t11);
	Vertexes.push_back(new Vertex());
	Vertexes[3]->Set(p111,xAxis,t01);
	Triangles.push_back(new Triangle());
	Triangles[0]->Init(Vertexes[0],Vertexes[1],Vertexes[2],mtl);
	Triangles.push_back(new Triangle());
	Triangles[1]->Init(Vertexes[0],Vertexes[2],Vertexes[3],mtl);

	// Left
	Vertexes.push_back(new Vertex());
	Vertexes[4]->Set(p000,-xAxis,t00);
	Vertexes.push_back(new Vertex());
	Vertexes[5]->Set(p001,-xAxis,t10);
	Vertexes.push_back(new Vertex());
	Vertexes[6]->Set(p011,-xAxis,t11);
	Vertexes.push_back(new Vertex());
	Vertexes[7]->Set(p010,-xAxis,t01);
	Triangles.push_back(new Triangle());
	Triangles[2]->Init(Vertexes[4],Vertexes[5],Vertexes[6],mtl);
	Triangles.push_back(new Triangle());
	Triangles[3]->Init(Vertexes[4],Vertexes[6],Vertexes[7],mtl);

	// Top
	Vertexes.push_back(new Vertex());
	Vertexes[8]->Set(p011,yAxis,t00);
	Vertexes.push_back(new Vertex());
	Vertexes[9]->Set(p111,yAxis,t10);
	Vertexes.push_back(new Vertex());
	Vertexes[10]->Set(p110,yAxis,t11);
	Vertexes.push_back(new Vertex());
	Vertexes[11]->Set(p010,yAxis,t01);
	Triangles.push_back(new Triangle());
	Triangles[4]->Init(Vertexes[8],Vertexes[9],Vertexes[10],mtl);
	Triangles.push_back(new Triangle());
	Triangles[5]->Init(Vertexes[8],Vertexes[10],Vertexes[11],mtl);

	// Bottom
	Vertexes.push_back(new Vertex());
	Vertexes[12]->Set(p000,-yAxis,t00);
	Vertexes.push_back(new Vertex());
	Vertexes[13]->Set(p100,-yAxis,t10);
	Vertexes.push_back(new Vertex());
	Vertexes[14]->Set(p101,-yAxis,t11);
	Vertexes.push_back(new Vertex());
	Vertexes[15]->Set(p001,-yAxis,t01);
	Triangles.push_back(new Triangle());
	Triangles[6]->Init(Vertexes[12],Vertexes[13],Vertexes[14],mtl);
	Triangles.push_back(new Triangle());
	Triangles[7]->Init(Vertexes[12],Vertexes[14],Vertexes[15],mtl);

	// Front
	Vertexes.push_back(new Vertex());
	Vertexes[16]->Set(p001,zAxis,t00);
	Vertexes.push_back(new Vertex());
	Vertexes[17]->Set(p101,zAxis,t10);
	Vertexes.push_back(new Vertex());
	Vertexes[18]->Set(p111,zAxis,t11);
	Vertexes.push_back(new Vertex());
	Vertexes[19]->Set(p011,zAxis,t01);
	Triangles.push_back(new Triangle());
	Triangles[8]->Init(Vertexes[16],Vertexes[17],Vertexes[18],mtl);
	Triangles.push_back(new Triangle());
	Triangles[9]->Init(Vertexes[16],Vertexes[18],Vertexes[19],mtl);

	// Back
	Vertexes.push_back(new Vertex());
	Vertexes[20]->Set(p100,-zAxis,t00);
	Vertexes.push_back(new Vertex());
	Vertexes[21]->Set(p000,-zAxis,t10);
	Vertexes.push_back(new Vertex());
	Vertexes[22]->Set(p010,-zAxis,t11);
	Vertexes.push_back(new Vertex());
	Vertexes[23]->Set(p110,-zAxis,t01);
	Triangles.push_back(new Triangle());
	Triangles[10]->Init(Vertexes[20],Vertexes[21],Vertexes[22],mtl);
	Triangles.push_back(new Triangle());
	Triangles[11]->Init(Vertexes[20],Vertexes[22],Vertexes[23],mtl);
}

bool MeshObject::LoadPLY(const char *filename, Material *mtl) {
	// Open file
	FILE *f = fopen(filename, "r");
	if (f == 0) {
		printf("ERROR: MeshObject::LoadPLY()- Can't open '%s'\n", filename);
		return false;
	}

	// Read header
	char tmp[256];
	int numverts = 0, numtris = 0;
	int posprop = -99, normprop = -99;
	int props = 0;
	while (1) {
		fgets(tmp, 256, f);
		if (strncmp(tmp, "element vertex", 14) == 0)
			numverts = atoi(&tmp[14]);
		if (strncmp(tmp, "element face", 12) == 0)
			numtris = atoi(&tmp[12]);
		if (strncmp(tmp, "property", 8) == 0) {
			int len = strlen(tmp);
			if (strncmp(&tmp[len - 3], " x", 2) == 0) posprop = props;
			if (strncmp(&tmp[len - 3], "nx", 2) == 0) normprop = props;
			props++;
		}
		if (strcmp(tmp, "end_header\n") == 0) break;
	}
	if (posprop == -1) {
		printf("ERROR: MeshObject::LoadPLY()- No vertex positions found\n");
		fclose(f);
		return false;
	}

	// Read verts
	int i = 0;
	if (numverts>0) {
		NumVertexes = numverts;

		for (i = 0; i<NumVertexes; i++) {
			fgets(tmp, 256, f);
			char *pch = strtok(tmp, " ");
			int prop = 0;
			while (pch) {
				Vertexes.push_back(new Vertex());
				if (prop == posprop) Vertexes[i]->Position.x = float(atof(pch));
				if (prop == posprop + 1) Vertexes[i]->Position.y = float(atof(pch));
				if (prop == posprop + 2) Vertexes[i]->Position.z = float(atof(pch));
				if (prop == normprop) Vertexes[i]->Normal.x = float(atof(pch));
				if (prop == normprop + 1) Vertexes[i]->Normal.y = float(atof(pch));
				if (prop == normprop + 2) Vertexes[i]->Normal.z = float(atof(pch));
				pch = strtok(0, " ");
				prop++;
			}
		}
	}

	// Read tris
	if (numtris>0) {
		if (mtl == 0) mtl = new LambertMaterial;
		NumTriangles = numtris;
		for (i = 0; i<numtris; i++) {
			int count, i0, i1, i2;
			fscanf(f, "%d %d %d %d\n", &count, &i0, &i1, &i2);
			if (count != 3) {
				printf("ERROR: MeshObject::LoadPLY()- Only triangles are supported\n");
				fclose(f);
				return false;
			}
			Triangles.push_back(new Triangle());
			Triangles[i]->Init(Vertexes[i0], Vertexes[i1], Vertexes[i2], mtl);
		}
	}

	// Smooth
	if (normprop<0) Smooth();

	// Close file
	fclose(f);
	printf("Loaded %d triangles from file '%s'\n", numtris, filename);
	return true;
}


void MeshObject::Smooth() {
	int i, j;
	for (i = 0; i<NumVertexes; i++)
		Vertexes[i]->Normal = glm::vec3(0);
	for (i = 0; i<NumTriangles; i++) {
		Triangle * tri = Triangles[i];
		glm::vec3 e1 = tri->GetVtx(1).Position - tri->GetVtx(0).Position;
		glm::vec3 e2 = tri->GetVtx(2).Position - tri->GetVtx(0).Position;
		glm::vec3 cross = glm::cross(e1, e2);
		for (j = 0; j<3; j++)
			tri->GetVtx(j).Normal += cross;
	}
	for (i = 0; i<NumVertexes; i++)
		Vertexes[i]->Normal = glm::normalize(Vertexes[i]->Normal);
}

vector<Triangle*>* MeshObject::GetTriangles()
{
	return &Triangles;
}



////////////////////////////////////////////////////////////////////////////////
