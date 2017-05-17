////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#pragma once

#include "Material.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial:public Material {
public:
	void SetColor(Color& col) {
		DiffuseColor = col;
	}
	void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
		float pi=3.1415926f;
		float nDotL = glm::dot(in, hit.Normal);
		if (nDotL < 0) nDotL = 0;
		col = DiffuseColor * col * nDotL;
	}
	void createCoordinateSystem(const glm::vec3 &N, glm::vec3 &Nt, glm::vec3 &Nb)
	{
		if (std::fabs(N.x) > std::fabs(N.y))
			Nt = glm::vec3(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z);
		else
			Nt = glm::vec3(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
		Nb = glm::cross(N, Nt);
	}
	void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) {
		float pi = 3.1415926f;
		float s = ((float)rand() / (RAND_MAX));
		float t = ((float)rand() / (RAND_MAX));
		float u = 2 * pi*s;
		float v = sqrt(1 - t);
		outDir = glm::vec3(v*cos(u), sqrt(t), v*sin(u));
		glm::vec3 rvec;
		do {
			float x = (float)rand() / (RAND_MAX);
			float y = (float)rand() / (RAND_MAX);
			float z = (float)rand() / (RAND_MAX);
			rvec = glm::vec3(x, y, z);
		} while (glm::dot(rvec, isect.Normal)== 1 
			|| (glm::dot(rvec, isect.Normal) == -1) 
			|| rvec == glm::vec3(0,0,0));
		glm::vec3 a = glm::cross(rvec, isect.Normal);
		glm::vec3 b = isect.Normal;
		glm::vec3 c = glm::cross(a, isect.Normal);
		//glm::vec3 a, b = isect.Normal, c;
		//createCoordinateSystem(b, a, c);
		outDir = glm::vec3(
			outDir.x * c.x + outDir.y * b.x + outDir.z * a.x,
			outDir.x * c.y + outDir.y * b.y + outDir.z * a.y,
			outDir.x * c.z + outDir.y * b.z + outDir.z * a.z);
		outColor = DiffuseColor;
	}

private:
	Color DiffuseColor;
};

////////////////////////////////////////////////////////////////////////////////
