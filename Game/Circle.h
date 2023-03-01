#ifndef CIRCLE_H
#define CIRCLE_H

#define _USE_MATH_DEFINES

#include<cmath>
#include<iostream>
#include<SFML/Graphics.hpp>

#include"Shape.h"

struct Circle : public Shape
{
	float radius;

	Circle();
	Circle(float x, float y, float radius);
	Circle(const Position &p, float radius);
	bool posIn(Position p) const;
	void draw(sf::RenderWindow &window, const sf::Color &color = sf::Color::White) const;
	//void draw(sf::RenderWindow &window, const Camera &camera, sf::Texture &texture) const;
};

#endif