#ifndef ELIPSE_H
#define ELIPSE_H

#define _USE_MATH_DEFINES

#include<cmath>
#include<iostream>
#include<SFML/Graphics.hpp>

#include"Shape.h"

struct Ellipse : public Shape
{
	float w;
	float h;

	Ellipse();
	Ellipse(float x, float y, float radius);
	Ellipse(float x, float y, float w, float h);
	Ellipse(const Position &p, float radius);
	Ellipse(const Position &p, float w, float h);
	Ellipse(const Position &xy, const Position &wh);
	bool posIn(Position p) const;
	void draw(sf::RenderWindow &window, const sf::Color &color = sf::Color::White) const;
	//void draw(sf::RenderWindow &window, const Camera &camera, sf::Texture &texture) const;
};

#endif