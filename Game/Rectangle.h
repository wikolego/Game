#ifndef RECTANGLE_H
#define RECTANGLE_H

#define _USE_MATH_DEFINES

#include<cmath>
#include<iostream>
#include<SFML/Graphics.hpp>

#include"Shape.h"

struct Rectangle: public Shape 
{
	float w;
	float h;

	Rectangle();
	Rectangle(float x, float y, float w, float h, float r = 0);
	Rectangle(const Position &p, float w, float h, float r = 0);
	Rectangle(const Position &xy, const Position &wh, float r = 0);
	Rectangle operator=(const Rectangle &r);
	bool posIn(Position p) const;
	void draw(sf::RenderWindow &window, const sf::Color &color = sf::Color::White) const;
};

#endif