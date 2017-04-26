#include "Camera.h"
#include <iostream>
Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::LookAt(vec position, vec target, vec up)
{
	vec d = position;
	vec c = glm::normalize(d - target);
	vec a = glm::normalize(glm::cross(up,c));
	vec b = glm::cross(c, a);
	mat4 cam(a.x, a.y, a.z, 0, b.x, b.y, b.z, 0, c.x, c.y, c.z, 0, d.x, d.y, d.z, 1);
	lookAt = cam;
}

void Camera::SetResolution(int w, int h)
{
	this->w = w;
	this->h = h;
}

void Camera::SetFOV(float fov)
{
	this->fov = fov;
}

void Camera::SetAspect(float aspect)
{
	this->aspect = aspect;
}

Color getColorAt(Scene &scene, Intersection &hit, Ray &ray, bool shadeStatus) 
{
	Color finalcol = finalcol.BLACK;
	for (auto ind = 0; ind < scene.GetNumLights(); ind++) {
		Light * lgt = &scene.GetLight(ind);
		Color lgtCol;
		vec toLight;
		vec ltPos;
		auto intensity = lgt->Illuminate(hit.Position, lgtCol, toLight, ltPos);
		Color lbt(lgtCol);
		hit.Mtl->ComputeReflectance(lbt, toLight, hit.Normal, hit);
		bool shadowed = false;
		if (shadeStatus) {
			Ray raySd;
			raySd.Origin = hit.Position;
			raySd.Direction = toLight;
			Intersection hitSd;
			if (scene.Intersect(raySd, hitSd)) {
				if (hitSd.HitDistance > 0 && hitSd.HitDistance < glm::length(ltPos))
					shadowed = true;
			}
		}
		if (!shadeStatus) {
			finalcol = finalcol + (lbt * intensity);
		}
		else
		{ 
			if (!shadowed) {
				finalcol = finalcol + (lbt * intensity);
			}
		}
		//if (nDotL) std::cout << nDotL << std::endl;
	}
	return finalcol;
}

void Camera::Render(Scene scene, bool shade)
{
	bitMap = new Bitmap(w, h);

	vec a = vec(lookAt[0]);
	vec b = vec(lookAt[1]);
	vec c = vec(lookAt[2]);
	vec d = vec(lookAt[3]);

	float aspectratio = (float)w / (float)h;
	float vfov = fov;
	float hfov = 2 * atan(aspect * tan(vfov/2 * pi /180));
	float scaleX = 2 * tan(hfov / 2); 
	float scaleY = 2 * tan(vfov / 2 * pi / 180);

	for (auto x = 0; x < w; x++) {
		for (auto y = 0; y < h; y++) {
			if (x == 0 && y == 203 || 1) {
				float fx = (float(x) + 0.5f) / float(w) - 0.5f;
				float fy = (float(y) + 0.5f) / float(h) - 0.5f;
				Ray ray;
				ray.Origin = d;
				ray.Direction = glm::normalize(fx*scaleX*a + fy*scaleY*b - c);

				Intersection hit;
				Color col;
				
				if (scene.Intersect(ray, hit)) {

					col = getColorAt(scene, hit, ray, shade);
				}
				else {
					col = scene.GetSkyColor();
				}
				bitMap->SetPixel(x, y, col.ToInt());
			}
		}
	}
}

void Camera::SaveBitmap(const char * filename)
{
	bitMap->SaveBMP(filename);
}
