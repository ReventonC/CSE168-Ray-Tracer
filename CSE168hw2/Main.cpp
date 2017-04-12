////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include "MeshObject.h"
#include "SphereObject.h"
#include "PlaneObject.h"
#include "InstanceObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Scene.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/random.hpp"
#include <time.h>

void project1();
void spheres();

////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {
	time_t t;
	srand((unsigned)time(&t));
	project1();
	spheres();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void project1() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Create boxes
	MeshObject box1; 
	box1.MakeBox(5.0f,0.1f,5.0f);
	scn.AddObject(box1);

	MeshObject box2;
	box2.MakeBox(1.0f,1.0f,1.0f);

	InstanceObject inst1(box2);
	glm::mat4x4 mtx=glm::rotate(glm::mat4x4(),0.5f,glm::vec3(1,0,0));
	mtx[3][1]=1.0f;
	inst1.SetMatrix(mtx); 
	scn.AddObject(inst1);

	// half box
	InstanceObject inst2(box2);
	mtx=glm::rotate(glm::mat4x4(),1.0f,glm::vec3(0,1,0));
	mtx[3] = glm::vec4(-1, 0, 1, 1);
	inst2.SetMatrix(mtx);
	scn.AddObject(inst2);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(0.5f);
	sunlgt.SetDirection(glm::vec3(-0.5f, -1.0f, -0.5f));
	scn.AddLight(sunlgt);

	PointLight redlgt;
	redlgt.SetBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.SetIntensity(2.0f);
	redlgt.SetPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	scn.AddLight(redlgt);

	// Create camera
	Camera cam;
	cam.LookAt(glm::vec3(2.0f,2.0f,5.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0,1,0));
	cam.SetResolution(800,600);
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);

	// Render image
	cam.Render(scn, 0);
	cam.SaveBitmap("project1.bmp");

	cam.Render(scn, 1);
	cam.SaveBitmap("project1_shade.bmp");
}

////////////////////////////////////////////////////////////////////////////////
void spheres() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.8f, 1.0f));

	// Create ground plane
	PlaneObject ground;
	scn.AddObject(ground);

	// Create spheres
	for (int i = 0; i<20; i++) {
		SphereObject *sphere = new SphereObject;
		float rad = glm::linearRand(0.25f, 0.5f);
		vec pos(glm::linearRand(-5.0f, 5.0f), rad, glm::linearRand(-5.0f, 5.0f));
		sphere->SetRadius(rad);
		sphere->SetCenter(pos);
		scn.AddObject(*sphere);
	}

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(vec(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);

	// Create camera
	Camera cam;
	cam.LookAt(vec(-3.75f, 0.25f, 6.0f), vec(0.0f, 0.5f, 0.0f), vec(0, 1, 0));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);

	// Render image
	cam.Render(scn, 0);
	cam.SaveBitmap("spheres.bmp");
	cam.Render(scn, 1);
	cam.SaveBitmap("spheres_shade.bmp");
}
