////////////////////////////////////////
// Scene.h
////////////////////////////////////////

#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>
#include <iostream>
#define vector std::vector

////////////////////////////////////////////////////////////////////////////////

class Scene {
public:
	Scene()										{SkyColor.Set(0.2f,0.2f,0.5f);}

	void AddObject(Object &obj)					{Objects.push_back(&obj);}
	void AddLight(Light &lgt)					{Lights.push_back(&lgt);}
	void SetSkyColor(const Color sky)			{SkyColor=sky;}

	int GetNumLights()							{return (int)Lights.size();}
	Light &GetLight(int i)						{return *Lights[i];}
	Color GetSkyColor()							{return SkyColor;}

	bool Intersect(const Ray &ray,Intersection &hit) {
		/*bool success=false;
		Intersection next;
		for(unsigned int i=0;i<Objects.size();i++) {
			if (Objects[i]->Intersect(ray, next)) success = true;
			//if (success) std::cout << next.HitDistance << " -1- "<< hit.HitDistance << std::endl;
			if ((next.HitDistance < hit.HitDistance || hit.HitDistance < 0) && next.HitDistance>0) {
				hit.Position = next.Position;
				hit.Normal = next.Normal;
				hit.HitDistance = next.HitDistance;
				hit.Mtl = next.Mtl;	
				//std::cout << next.HitDistance << " -2- " << hit.HitDistance << std::endl;
			}

		}
		if (hit.HitDistance > 0) return success;
		return false; */
		bool success = false;
		for (int i = 0; i < Objects.size(); i++) {
			if (Objects.at(i)->Intersect(ray, hit)) success = true;
		}
		return success;
	}

private:
	vector<Object*> Objects;
	vector<Light*> Lights;
	Color SkyColor;
};

////////////////////////////////////////////////////////////////////////////////
