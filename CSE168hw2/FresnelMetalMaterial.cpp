#include "FresnelMetalMaterial.h"
#include <iostream>


FresnelMetalMaterial::FresnelMetalMaterial()
{
}


FresnelMetalMaterial::~FresnelMetalMaterial()
{
}

void FresnelMetalMaterial::ComputeReflectance(Color & col, const glm::vec3 & in, const glm::vec3 & out, const Intersection & hit)
{
	col = Color(0, 0, 0);
	/*float nDotL = glm::dot(in, hit.Normal);
	glm::vec3 refdir = 2 * nDotL * hit.Normal - in;
	if (glm::dot(refdir, out)==1) {
		col = SpecularColor;
	}
	else {
		col = Color(0, 0, 0);
	}*/
}

void FresnelMetalMaterial::GenerateSample(const Intersection & isect, 
	const glm::vec3 & inDir, glm::vec3 & outDir, Color & outColor)
{
	float nDotL = glm::dot(inDir, isect.Normal);
	outDir = -2 * nDotL * isect.Normal + inDir;
	outColor = SpecularColor;
}
