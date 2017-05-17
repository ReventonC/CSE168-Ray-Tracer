////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include "MeshObject.h"
#include "BoxTreeObject.h"
#include "SphereObject.h"
#include "PlaneObject.h"
#include "InstanceObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Scene.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp" 
#include "glm/gtc/random.hpp"
#include <time.h>
#include <ctime>
#include <iostream>
#include <string>
#include "FresnelMetalMaterial.h"
#include "AshikhminMaterial.h"

#define PI 3.14159265359

void project1();
void spheres();
void project2();
void project3();
void project4();

////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {
	time_t t;
	srand((unsigned)time(&t));

	//project1();
	//spheres();
	//project2();
	//project3();
	project4();

	std::cout << "Press ENTER to quit";
	std::string ept;
	std::getline(std::cin, ept);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void project4() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
	// Materials
	const int nummtls = 4;
	AshikhminMaterial mtl[nummtls];
	// Diffuse
	mtl[0].SetSpecularLevel(0.0f);
	mtl[0].SetDiffuseLevel(1.0f);
	mtl[0].SetDiffuseColor(Color(0.7f, 0.7f, 0.7f));
	// Roughened copper
	mtl[1].SetDiffuseLevel(0.0f);
	mtl[1].SetSpecularLevel(1.0f);
	mtl[1].SetSpecularColor(Color(0.9f, 0.6f, 0.5f));
	mtl[1].SetRoughness(100.0f, 100.0f);
	// Anisotropic gold
	mtl[2].SetDiffuseLevel(0.0f);
	mtl[2].SetSpecularLevel(1.0f);
	mtl[2].SetSpecularColor(Color(0.95f, 0.7f, 0.3f));
	mtl[2].SetRoughness(1.0f, 1000.0f);
	// Red plastic
	mtl[3].SetDiffuseColor(Color(1.0f, 0.1f, 0.1f));
	mtl[3].SetDiffuseLevel(0.8f);
	mtl[3].SetSpecularLevel(0.2f);
	mtl[3].SetSpecularColor(Color(1.0f, 1.0f, 1.0f));
	mtl[3].SetRoughness(1000.0f, 1000.0f);
	// Load dragon mesh
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);
	// Create box tree
	BoxTreeObject tree;
	tree.Construct(dragon);
	// Create dragon instances
	glm::mat4x4 mtx;
	for (int i = 0; i<nummtls; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx[3] = glm::vec4(0.0f, 0.0f, -0.1f*float(i), 1.0f);
		inst->SetMatrix(mtx);
		inst->SetMaterial(&mtl[i]);
		scn.AddObject(*inst);
	}
	// Create ground
	LambertMaterial lambert;
	lambert.SetColor(Color(0.3f, 0.3f, 0.35f));
	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &lambert);
	scn.AddObject(ground);
	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);
	// Create camera
	Camera cam;
	cam.LookAt(glm::vec3(-0.5f, 0.25f, -0.2f), glm::vec3(0.0f, 0.15f, -0.15f), glm::vec3(0, 1.0f, 0));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(10, 10);
	cam.SetJitter(true);
	cam.SetShirley(true);
	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project3.bmp");
}

void project3() {
	std::cout << "Project 3" << std::endl << std::endl;

	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
	// Create ground
	LambertMaterial groundMtl;
	groundMtl.SetColor(Color(0.25f, 0.25f, 0.25f));
	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &groundMtl);
	scn.AddObject(ground);
	// Load dragon mesh
	MeshObject dragon;


	std::cout << "- LoadPLY Timer started" << std::endl << "  ";
	std::clock_t timer = std::clock();

	dragon.LoadPLY("dragon.ply", 0);


	double timeused = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	std::cout << "  LoadPLY Time Used: " << timeused << std::endl << std::endl;

	// Create box tree
	BoxTreeObject tree;

	std::cout << "- Construct BoxTree Timer started" << std::endl;
	timer = std::clock();

	tree.Construct(dragon);


	timeused = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	std::cout << "  Construct BoxTree Time Used: " << timeused << std::endl << std::endl;

	// Materials
	LambertMaterial white;
	white.SetColor(Color(0.7f, 0.7f, 0.7f));
	LambertMaterial red;
	red.SetColor(Color(0.7f, 0.1f, 0.1f));
	FresnelMetalMaterial metal;
	//LambertMaterial metal;
	metal.SetColor(Color(0.95f, 0.64f, 0.54f));
	const int numDragons = 4;
	Material *mtl[numDragons] = { &white,&metal,&red,&white };
	// Create dragon instances
	glm::mat4x4 mtx;
	for (int i = 0; i<numDragons; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx[3] = glm::vec4(0.0f, 0.0f, 0.3f*(float(i) / float(numDragons - 1) - 0.5f), 1.0f);
		inst->SetMatrix(mtx);
		inst->SetMaterial(mtl[i]);
		scn.AddObject(*inst);
	}
	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);
	// Create camera
	Camera cam;
	int w = 3000, h = 2000;
	cam.SetResolution(w, h);
	cam.SetAspect(1.33f);
	cam.LookAt(glm::vec3(-0.5f, 0.25f, -0.2f), glm::vec3(0.0f, 0.15f, 0.0f), glm::vec3(0, 1.0f, 0));
	cam.SetFOV(40.0f);

	int sx = 20, sy = 20;
	bool jt = 1, sl = 1;
	cam.SetSuperSample(sx,sy);
	cam.SetJitter(jt);
	cam.SetShirley(sl);
	// Render image
	std::cout << "- Render Settings" << std::endl;
	std::cout << "  Resolution: " << w << " x " << h << std::endl;
	std::cout << "  SuperSample: " << sx << " x " << sy << std::endl;
	std::string status = jt == 1 ? "On" : "Off";
	std::cout << "  Jitter:      " << status << std::endl;
	status = sl == 1 ? "On" : "Off";
	std::cout << "  Shirley:     " << status << std::endl << std::endl;



	std::cout << "- Render Timer started" << std::endl;
	timer = std::clock();

	cam.Render(scn);

	timeused = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	std::cout << "  Render Time Used: " << timeused << std::endl << std::endl;

	cam.SaveBitmap("project3.bmp");
}

void project2() {

	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.8f, 1.0f));

	// Create ground
	MeshObject ground;
	ground.MakeBox(5.0f, 0.1f, 5.0f);
	scn.AddObject(ground);

	std::cout << "LoadPLY Timer started." << std::endl << "  ";
	std::clock_t timer = std::clock();

	// Create dragon
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);
	dragon.Smooth();

	double timeused = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	std::cout << "LoadPLY Time Used: " << timeused << std::endl;


	std::cout << "Construct BoxTree Timer started." << std::endl;
	timer = std::clock();

	BoxTreeObject tree;
	tree.Construct(dragon);
	scn.AddObject(tree);

	timeused = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	std::cout << "Construct BoxTree Time Used: " << timeused << std::endl;

	// Create instance
	InstanceObject inst(tree);
	glm::mat4x4 mtx = glm::eulerAngleY(PI);
	mtx[3] = glm::vec4(-0.05f, 0.0f, -0.1f, 1.0f);
	inst.SetMatrix(mtx);
	scn.AddObject(inst);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);

	PointLight redlgt;
	redlgt.SetBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.SetIntensity(0.02f);
	redlgt.SetPosition(glm::vec3(-0.2f, 0.2f, 0.2f));
	scn.AddLight(redlgt);

	PointLight bluelgt;
	bluelgt.SetBaseColor(Color(0.2f, 0.2f, 1.0f));
	bluelgt.SetIntensity(0.02f);
	bluelgt.SetPosition(glm::vec3(0.1f, 0.1f, 0.3f));
	scn.AddLight(bluelgt);

	// Create camera
	Camera cam;
	cam.LookAt(glm::vec3(-0.1f, 0.1f, 0.2f), glm::vec3(-0.05f, 0.12f, 0.0f), glm::vec3(0, 1.0f, 0));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(1, 1);
	cam.SetJitter(1);
	cam.SetShirley(1);
	// Render image
	std::cout << "Render Timer started." << std::endl<< "  "; 
	timer = std::clock();
	cam.Render(scn);
	timeused = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	std::cout << "Render Time Used: " << timeused << std::endl << std::endl;
	cam.SaveBitmap("project2.bmp");
}

void project1() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));

	LambertMaterial groundMtl;
	groundMtl.SetColor(Color(0.25f, 0.25f, 0.25f));
	// Create boxes
	MeshObject box1;
	box1.MakeBox(5.0f, 0.1f, 5.0f, &groundMtl);
	//scn.AddObject(box1);

	BoxTreeObject tree1;
	tree1.Construct(box1);
	scn.AddObject(tree1);

	MeshObject box2;
	box2.MakeBox(1.0f, 1.0f, 1.0f);

	BoxTreeObject tree2;
	tree2.Construct(box2);

	LambertMaterial red;
	red.SetColor(Color(0.7f, 0.1f, 0.1f));
	InstanceObject inst1(tree2);
	inst1.SetMaterial(&red);
	glm::mat4x4 mtx = glm::rotate(glm::mat4x4(), 0.5f, glm::vec3(1, 0, 0));
	mtx[3][1] = 1.0f;
	inst1.SetMatrix(mtx);
	scn.AddObject(inst1);


	// half box
	LambertMaterial white;
	white.SetColor(Color(0.7f, 0.7f, 0.7f));
	InstanceObject inst2(tree2);
	inst2.SetMaterial(&white);
	mtx = glm::rotate(glm::mat4x4(), 1.0f, glm::vec3(0, 1, 0));
	mtx[3] = glm::vec4(-1, 0, 1, 1);
	inst2.SetMatrix(mtx);
	scn.AddObject(inst2);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.f);
	sunlgt.SetDirection(glm::vec3(-0.5f, -1.0f, -0.5f));
	scn.AddLight(sunlgt);

	/*PointLight redlgt;
	redlgt.SetBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.SetIntensity(2.0f);
	redlgt.SetPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	scn.AddLight(redlgt);*/

	// Create camera
	Camera cam;
	cam.LookAt(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));
	cam.SetResolution(800, 600);
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);

	cam.SetSuperSample(2,2);
	cam.SetJitter(1);
	cam.SetShirley(1);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project1_shade.bmp");
}

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
	cam.SetResolution(600,480);

	cam.SetSuperSample(2, 2);
	cam.SetJitter(true);
	cam.SetShirley(true);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("spheres.bmp");
	cam.Render(scn);
	cam.SaveBitmap("spheres_shade.bmp");
}
