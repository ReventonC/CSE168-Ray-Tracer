#include "DirectLight.h"


DirectLight::DirectLight()
{
}


DirectLight::~DirectLight()
{
}

float DirectLight::Illuminate(const glm::vec3 & pos, Color & col, glm::vec3 & toLight, glm::vec3 & ltPos)
{
	toLight = -Direction;
	col = BaseColor;
	glm::vec3 dir = Direction;
	ltPos = pos - dir * 1000000.0f;
	// Create virtual position
	return Intensity;
}

void DirectLight::SetDirection(glm::vec3 & dir)
{
	Direction = glm::normalize(dir);
}