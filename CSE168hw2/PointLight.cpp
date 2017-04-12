#include "PointLight.h"


PointLight::PointLight()
{
}

float PointLight::Illuminate(const glm::vec3 & pos, Color & col, glm::vec3 & toLight, glm::vec3 & ltPos)
{
	toLight = Position - pos;
	float bright = Intensity / (glm::length(toLight)*glm::length(toLight));
	// Inverse square falloff
	toLight = glm::normalize(toLight);
	col = BaseColor;
	ltPos = Position;
	return bright;
}

void PointLight::SetPosition(glm::vec3 & pos)
{
	Position = pos;
}


PointLight::~PointLight()
{
}
