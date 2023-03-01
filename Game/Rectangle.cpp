#include"Rectangle.h"

Rectangle::Rectangle()
{
	type = ShapeType::Rectangle;
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	rotation = 0;
}

Rectangle::Rectangle(float x, float y, float w, float h, float r)
{
	type = ShapeType::Rectangle;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	rotation = r;
}

Rectangle::Rectangle(const Position &p, float w, float h, float r)
{
	type = ShapeType::Rectangle;
	x = p.x;
	y = p.y;
	this->w = w;
	this->h = h;
	rotation = r;
}

Rectangle::Rectangle(const Position &xy, const Position &wh, float r)
{
	type = ShapeType::Rectangle;
	x = xy.x;
	y = xy.y;
	w = wh.x;
	h = wh.y;
	rotation = r;
}

Rectangle Rectangle::operator=(const Rectangle &r)
{
	x = r.x;
	y = r.y;
	w = r.w;
	h = r.h;
	return *this;
}

bool Rectangle::posIn(Position p) const
{
	p.rotate(Position(x, y), -rotation);
	return (x <= p.x && p.x <= x + w) && (y <= p.y && p.y <= y + h);
}

void Rectangle::draw(sf::RenderWindow &window, const sf::Color &color) const
{
	sf::RectangleShape rect;
	rect.setPosition(x, y);
	rect.setSize({ w, h });
	rect.setRotation(rotation);
	rect.setFillColor(color);
	window.draw(rect);
}