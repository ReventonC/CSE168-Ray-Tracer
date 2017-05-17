#pragma once
class Color
{

private:

	float r, g, b;

public:

	Color();
	Color(float Ar, float Ag, float Ab);
	Color(const Color * Acolor);
	void Set(float Ar, float Ag, float Ab);
	void Set(const Color Acolor);
	Color getColor(const Color Acolor);
	float getr() { return r; }
	float getg() { return g; }
	float getb() { return b; }

	Color operator+(Color col);
	Color operator-(Color col);
	Color operator+(float delta);
	Color operator*(float delta);
	Color operator*(Color col);
	Color operator/(float delta);


	int ToInt();
	void FromInt(int c);
	Color fix();

	static Color WHITE, GREY, BLACK;
	static Color RED, YELLOW, BLUE, GREEN;

	~Color();
};

