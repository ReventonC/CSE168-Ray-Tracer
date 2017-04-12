#pragma once
#include "Ray.h"
#include "Color.h"
#include <iostream>
#include "Material.h"
#include "Vertex.h"

#define vec glm::vec3
#define mat4 glm::mat4
#define mat3 glm::mat3

class Object
{
public:
	Object();

	virtual bool Intersect(const Ray & ray, Intersection & hit)=0;

	~Object();
};

