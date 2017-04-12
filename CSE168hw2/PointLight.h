#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();
	float Illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos);
	void SetPosition(glm::vec3 &pos);
private: 
	glm::vec3 Position;
};

