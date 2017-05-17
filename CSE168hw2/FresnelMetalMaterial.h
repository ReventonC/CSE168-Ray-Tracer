#pragma once
#include "Material.h"
class FresnelMetalMaterial :
	public Material
{
public:
	FresnelMetalMaterial();
	~FresnelMetalMaterial();
	void SetColor(Color& col) {
		SpecularColor = col;
	}
	void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);

private:
	Color SpecularColor;
};

