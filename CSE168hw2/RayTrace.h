#pragma once
#include "Camera.h"
class RayTrace
{
public:
	RayTrace();
	RayTrace(Scene &s);
	~RayTrace();
	bool TraceRay(const Ray &ray, Intersection &hit, int depth = 1);
	int getpr() { return PrimaryRays; }
	void incpr() { PrimaryRays++; }
	int getsd() { return ShadowRays; }
	int getse() { return SecondaryRays; }


private:
	Scene *Scn;
	// Settings
	int MaxDepth = 10;
	// Statistics
	int PrimaryRays = 0;
	int SecondaryRays = 0;
	int ShadowRays = 0;
};

