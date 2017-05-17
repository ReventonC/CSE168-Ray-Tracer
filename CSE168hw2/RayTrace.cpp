#include "RayTrace.h"


RayTrace::RayTrace()
{
}

RayTrace::RayTrace(Scene & s)
{
	Scn = &s;
}


RayTrace::~RayTrace()
{
}

bool RayTrace::TraceRay(const Ray & ray, Intersection & hit, int depth)
{
	// Find ray intersection
	if (Scn->Intersect(ray, hit) == false) {
		hit.Shade = Scn->GetSkyColor();
		return false;
	}

	hit.Shade = hit.Shade.BLACK;

	for (auto ind = 0; ind < Scn->GetNumLights(); ind++) {

		Light * lgt = &Scn->GetLight(ind);
		Color lgtCol;
		vec toLight;
		vec ltPos;
		auto intensity = lgt->Illuminate(hit.Position, lgtCol, toLight, ltPos);
		Color lbt(lgtCol);
		hit.Mtl->ComputeReflectance(lbt, toLight, ray.Direction, hit);

		bool shadowed = false;
		Ray raySd;
		ShadowRays++;
		raySd.Origin = hit.Position;
		raySd.Direction = toLight;
		Intersection hitSd;
		if (Scn->Intersect(raySd, hitSd)) {
			if (hitSd.HitDistance > 0 && hitSd.HitDistance < glm::length(ltPos - raySd.Origin))
				shadowed = true;
		}
		if (!shadowed) {
			hit.Shade = hit.Shade + (lbt * intensity);
		}
	}
	if (depth == MaxDepth) {
		return true;
	}
	// Compute shade due to reflections/refractions
	Color secCol = secCol.BLACK;
	Ray secRay;
	SecondaryRays++;
	secRay.Origin = hit.Position;
	hit.Mtl->GenerateSample(hit, ray.Direction, secRay.Direction, secCol);
	Intersection secHit;
	//Compute ray intensity(based on fr or ft, for example)
	TraceRay(secRay, secHit, depth + 1);
	hit.Shade = hit.Shade + (secHit.Shade * secCol);


	return true;
}
