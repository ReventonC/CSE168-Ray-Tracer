#include "Color.h"

Color::Color(float Ar, float Ag, float Ab)
{
	r = Ar;
	g = Ag;
	b = Ab;
}

Color::Color(const Color * Acolor)
{
	r = Acolor->r;
	g = Acolor->g;
	b = Acolor->b;
}

void Color::Set(float Ar, float Ag, float Ab)
{
	r = Ar;
	g = Ag;
	b = Ab;
}

void Color::Set(const Color Acolor)
{
	r = Acolor.r;
	g = Acolor.g;
	b = Acolor.b;
}

Color Color::getColor(const Color Acolor)
{
	return Color(&Acolor);
}

Color::Color(): r(0), g(0), b(0) {}

Color Color::operator+(Color col)
{
	Color ret;
	ret.r = this->r + col.r;
	ret.g = this->g + col.g;
	ret.b = this->b + col.b;

	return ret;
}

Color Color::operator-(Color col)
{
	Color ret;
	ret.r = this->r - col.r;
	ret.g = this->g - col.g;
	ret.b = this->b - col.b;
	return ret;
}

Color Color::operator+(float delta)
{
	Color ret;
	ret.r = this->r + delta;
	ret.g = this->g + delta;
	ret.b = this->b + delta;
	return ret;
}

Color Color::operator*(float delta)
{
	Color ret;
	ret.r = this->r * delta;
	ret.g = this->g * delta;
	ret.b = this->b * delta;
	return ret;
}

Color Color::operator*(Color col)
{
	Color ret;
	ret.r = this->r * col.r;
	ret.g = this->g * col.g;
	ret.b = this->b * col.b;
	return ret;
}

Color Color::operator/(float delta)
{
	if (delta == 0) return Color(this->r, this->g, this->b);
	Color ret;
	ret.r = this->r / delta;
	ret.g = this->g / delta;
	ret.b = this->b / delta;
	return ret;
}

int Color::ToInt() 
{
	int Red = (r<0) ? 0 : ((r >= 1.0) ? 255 : int(r*256.0f));
	int Green = (g<0) ? 0 : ((g >= 1.0) ? 255 : int(g*256.0f));
	int Blue = (b<0) ? 0 : ((b >= 1.0) ? 255 : int(b*256.0f));
	return (Red << 16) | (Green << 8) | Blue;
}

void Color::FromInt(int c)
{
	Set(float((c >> 16) & 0xff) / 255.0f, float((c >> 8) & 0xff) / 255.0f, float(c & 0xff) / 255.0f);
}


Color Color::fix()
{
	if (r > 255) r = 255; else if (r < 0) r = 0;
	if (g > 255) g = 255; else if (g < 0) g = 0;
	if (b > 255) b = 255; else if (b < 0) b = 0;

	return Color(r, g, b);
}


Color::~Color()
{
}

Color Color::WHITE(1.0, 1.0, 1.0);
Color Color::GREY(0.25, 0.25, 0.25);
Color Color::BLACK(0.0, 0.0, 0.0);
Color Color::RED(1.0, 0.0, 0.0);
Color Color::YELLOW(1.0, 1.0, 0.0);
Color Color::BLUE(0.0, 0.0, 1.0);
Color Color::GREEN(0.0, 0.75, 0.0);
