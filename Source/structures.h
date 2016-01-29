#pragma once
class vec2 {
public:
	vec2() : x(0), y(0) {};
	vec2(float x, float y) : x(x), y(y) {};

	float x;
	float y;
};

class rgba {
public:
	rgba() : r(0), g(0), b(0), a(0) {};
	rgba(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};

	int r;
	int g;
	int b;
	int a;
};