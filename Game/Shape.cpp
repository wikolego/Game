#include"Shape.h"

Shape::Shape()
{
	type = ShapeType::NONE;
}

bool Shape::posIn(Position p) const
{
	printf("undefined\n");
	return true;
}

void Shape::rotate(float r)
{
	rotation = fixRotation(rotation + r);
}

void Shape::move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Shape::move(const Position &p)
{
	x += p.x;
	y += p.y;
}

void Shape::setPosition(const Position &p)
{
	x = p.x;
	y = p.y;
}

Position Shape::getPosition() const
{
	return Position(x, y);
}

float fixRotation(float rotation)
{
	if (rotation < 0)
		rotation += 360;
	else if (rotation >= 360)
		rotation -= 360;
	return rotation;
}