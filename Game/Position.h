#ifndef POSITION_H
#define POSITION_H

#define PRINT(X) cout << #X " = " << X << "\n"

#define _USE_MATH_DEFINES

#include<cmath>
#include<iostream>

#include"MathDefines.h"

struct Position
{
	float x;
	float y;
	Position()
	{
		x = 0;
		y = 0;
	}
	Position(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
	void operator=(const Position &p)
	{
		x = p.x;
		y = p.y;
	}
	Position operator*(float number) const
	{
		return Position(x * number, y * number);
	}
	Position operator/(float number) const
	{
		return Position(x / number, y / number);
	}
	Position operator+(const Position &p) const
	{
		return Position(x + p.x, y + p.y);
	}
	Position operator-(const Position &p) const
	{
		return Position(x - p.x, y - p.y);
	}
	void operator+=(const Position &p)
	{
		x += p.x;
		y += p.y;
	}
	bool operator==(const Position &p) const
	{
		return x == p.x && y == p.y;
	}
	bool operator!=(const Position &p) const
	{
		return !(x == p.x && y == p.y);
	}
	void rotate(float r)
	{
		rotate(COS(r), SIN(r));
	}
	void rotate(float cosinus, float sinus)
	{
		Position new_p = *this;

		new_p.x = x * cosinus - y * sinus;
		new_p.y = x * sinus + y * cosinus;

		*this = new_p;
	}
	void rotate(const Position &p, float r)
	{
		this->rotate(p, COS(r), SIN(r));
	}
	void rotate(const Position &p, float cosinus, float sinus)
	{
		Position cop = *this - p;

		x = cop.x * cosinus - cop.y * sinus;
		y = cop.x * sinus + cop.y * cosinus;

		*this += p;
	}
	float distance(const Position &p) const
	{
		return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
	}
	float direction(const Position &p) const
	{
		return ATAN2(p.x - x, p.y - y);
	}
	void print(const char *s = "") const
	{
		printf("x = %f, y = %f%s", x, y, s);
	}
};

typedef Position Pos;

#endif