#include"Ellipse.h"

Ellipse::Ellipse()
{
	type = ShapeType::Ellipse;
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	rotation = 0;
}

Ellipse::Ellipse(float x, float y, float radius)
{
	type = ShapeType::Ellipse;
	this->x = x;
	this->y = y;
	w = radius;
	h = radius;
	rotation = 0;
}

Ellipse::Ellipse(float x, float y, float w, float h)
{
	type = ShapeType::Ellipse;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	rotation = 0;
}

Ellipse::Ellipse(const Position &p, float radius)
{
	type = ShapeType::Ellipse;
	x = p.x;
	y = p.y;
	w = radius;
	h = radius;
	rotation = 0;
}

Ellipse::Ellipse(const Position &p, float w, float h)
{
	type = ShapeType::Ellipse;
	x = p.x;
	y = p.y;
	this->w = w;
	this->h = h;
	rotation = 0;
}

Ellipse::Ellipse(const Position &xy, const Position &wh)
{
	type = ShapeType::Ellipse;
	x = xy.x;
	y = xy.y;
	w = wh.x;
	h = wh.y;
	rotation = 0;
}

bool Ellipse::posIn(Position p) const
{
	p.rotate({x, y}, -rotation);
	float dx = p.x - x;
	float dy = p.y - y;
	return (dx * dx) / (w * w) + (dy * dy) / (h * h) <= 1;
}

void Ellipse::draw(sf::RenderWindow &window, const sf::Color &color) const
{
	sf::CircleShape ellipse;
	Position pos = Position(x - w, y - h);
	pos.rotate({x, y}, rotation);
	ellipse.setPosition(pos.x, pos.y);
	ellipse.setRotation(rotation);
	if (w > h)
	{
		ellipse.setRadius(w);
		ellipse.setScale(1, h / w);
	}
	else
	{
		ellipse.setRadius(h);
		ellipse.setScale(w / h, 1);
	}
	ellipse.setFillColor(color);
	window.draw(ellipse);
}