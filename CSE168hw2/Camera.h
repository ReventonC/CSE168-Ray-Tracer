#pragma once
#include "Ray.h"
#include "Scene.h"
#include "Bitmap.h"
#include "LambertMaterial.h"

#define vec glm::vec3
#define mat4 glm::mat4
#define mat3 glm::mat3
class Camera
{
	const float pi = 3.1415926f;

public:
	Camera();
	~Camera();

	void LookAt(vec position, vec target, vec up);
	void SetResolution(int, int);
	void SetFOV(float);
	void SetAspect(float);
	void Render(Scene, bool);
	void SaveBitmap(const char *filename);

private:
	mat4 lookAt;
	int w = 0;
	int h= 0;
	float fov;
	float aspect;
	Bitmap *bitMap;
};

