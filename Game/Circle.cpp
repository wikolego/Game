#include"Circle.h"

Circle::Circle()
{
	type = ShapeType::Circle;
	x = 0;
	y = 0;
	rotation = 0;
	radius = 0;
}

Circle::Circle(float x, float y, float radius)
{
	type = ShapeType::Circle;
	this->x = x;
	this->y = y;
	rotation = 0;
	this->radius = radius;
}

Circle::Circle(const Position &p, float radius)
{
	type = ShapeType::Circle;
	x = p.x;
	y = p.y;
	rotation = 0;
	this->radius = radius;
}

bool Circle::posIn(Position p) const
{
	float dx = p.x - x;
	float dy = p.y - y;
	return dx * dx + dy * dy <= radius * radius;
}

void Circle::draw(sf::RenderWindow &window, const sf::Color &color) const
{
	sf::CircleShape circle;
	circle.setPosition(x - radius, y - radius);
	circle.setRadius(radius);
	circle.setFillColor(color);
	window.draw(circle);
}