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

void makeSupersample(int x, int y, int xSam, int ySam, vector<vec> &sams) {
	sams.clear();
	for (auto i = 0; i < xSam; i++)
		for (auto j = 0; j < ySam; j++) {
			float fx = (float)x + (float)i / (float)xSam;
			float fy = (float)y + (float)j / (float)ySam;
			sams.push_back(vec(fx, fy, 0));
		}
}

void Camera::Render(Scene scene)
{
	srand(time(NULL));
	bitMap = new Bitmap(w, h);

	vec a = vec(lookAt[0]);
	vec b = vec(lookAt[1]);
	vec c = vec(lookAt[2]);
	vec d = vec(lookAt[3]);

	float aspectratio = (float)w / (float)h;
	float vfov = fov;
	float hfov = 2 * atan(aspect * tan(vfov / 2 * pi / 180));
	float scaleX = 2 * tan(hfov / 2);
	float scaleY = 2 * tan(vfov / 2 * pi / 180);
	RayTrace tracer(scene);

	int percent = w / 100;
	int checkendl = 0;
	std::cout << "  ";
	for (int x = 0; x < w; x++) {
		if ((x + 1) % percent == 0) {
			if (x + 1 == w) {
				std::cout << "100% Finished!";
			}
			else std::cout << (x + 1) / percent * 5 << "%...";
			checkendl++;
			if (checkendl % 10 == 0) {
				std::cout << std::endl << "  ";
			}
		}

		for (int y = 0; y < h; y++) {
			if (x == 10 && y == 240 || 1) {
				Ray ray;
				ray.Origin = d;
				Color col;

				vector<vec> supersample;
				makeSupersample(x, y, xSamples, ySamples, supersample);
				bool isHit = false;
				for (auto i = 0; i < supersample.size(); i++) {
					vec Asam = supersample.at(i);
					if (EnableJitter) {
						float rx = ((float)rand() / (RAND_MAX));
						float ry = ((float)rand() / (RAND_MAX));

						Asam.x += rx / (float)xSamples;
						Asam.y += ry / (float)ySamples;
					}
					else {
						Asam.x = (float(Asam.x) + 0.5f / (float)xSamples);
						Asam.y = (float(Asam.y) + 0.5f / (float)ySamples);
					}

					if (EnableShirley) {
						if (Asam.x - x < 0.5) Asam.x = x - 0.5 + sqrt(2 * (Asam.x - x));
						else Asam.x = x + 1.5 - sqrt(2 - 2 * (Asam.x - x));

						if (Asam.y - y < 0.5) Asam.y = y - 0.5 + sqrt(2 * (Asam.y - y));
						else Asam.y = y + 1.5 - sqrt(2 - 2 * (Asam.y - y));
					}

					Asam.x = Asam.x / float(w) - 0.5f;
					Asam.y = Asam.y / float(h) - 0.5f;

					ray.Direction = glm::normalize(Asam.x*scaleX*a + Asam.y*scaleY*b - c);

					Intersection hit;
					isHit = tracer.TraceRay(ray, hit, 0);
					tracer.incpr();

					col = col + hit.Shade;
				}
				col = col / (float)supersample.size();

				bitMap->SetPixel(x, y, col.ToInt());
			}

		}
	}
	std::cout << "Statistics:" << std::endl;
	std::cout << "    Num of PrimaryRays:   " << tracer.getpr() << std::endl;
	std::cout << "    Num of ShadowRays:    " << tracer.getsd() << std::endl;
	std::cout << "    Num of SecondaryRays: " << tracer.getse() << std::endl;
}

void Camera::SaveBitmap(const char * filename)
{
	bitMap->SaveBMP(filename);
}

void Camera::SetSuperSample(int xsp, int ysp)
{
	xSamples = xsp;
	ySamples = ysp;
}

void Camera::SetJitter(bool tf)
{
	EnableJitter = tf;
}

void Camera::SetShirley(bool tf)
{
	EnableShirley = tf;
}
