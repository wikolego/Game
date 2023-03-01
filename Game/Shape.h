#ifndef SHAPE_H
#define SHAPE_H

//class Camera;
#include"Position.h"

#include<SFML\Graphics.hpp>

enum class ShapeType
{
	Rectangle,
	Circle,
	Ellipse,
	NONE
};

struct Shape
{
	ShapeType type;

	float x;
	float y;
	float rotation;

	Shape();
	virtual bool posIn(Position p) const = 0;
	void rotate(float r);
	void move(float x, float y);
	void move(const Position &p);
	void setPosition(const Position &p);
	Position getPosition() const;
	virtual void draw(sf::RenderWindow &window, const sf::Color &color = sf::Color::White) const = 0;
};

float fixRotation(float rotation);

#endif