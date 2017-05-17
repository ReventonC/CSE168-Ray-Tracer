#pragma once
#include "Material.h"
class AshikhminMaterial :
	public Material
{
public:
	void SetColor(Color& col) {
		AshikCol = col;
	}
	void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	AshikhminMaterial();
	~AshikhminMaterial();
	void SetSpecularLevel(float a) { specLvl = a; }
	void SetSpecularColor(Color col) { specCol = col; }
	void SetDiffuseLevel(float a) { diffLvl = a; }
	void SetDiffuseColor(Color col) { diffCol = col; }
	void SetRoughness(float a, float b) { roughx = a; roughy = b; }
private:
	Color AshikCol, specCol, diffCol;
	float specLvl, diffLvl, roughx, roughy;
};

