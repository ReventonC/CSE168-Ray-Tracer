////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#pragma once

#include "Material.h"

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

private:
	Color DiffuseColor;
};

////////////////////////////////////////////////////////////////////////////////
