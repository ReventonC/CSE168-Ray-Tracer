#pragma once
#include "Light.h"
class DirectLight : public Light
{
public:
	DirectLight();
	~DirectLight();
	float Illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos);
	void SetDirection(glm::vec3 &dir);
	
private:
	glm::vec3 Direction;
};

