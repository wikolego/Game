#include"DynamicObject.h"

DynamicObject::DynamicObject()
{
	m_position = Position(0, 0);
	m_rotation = 0;

	m_rotation_v = 0;
	m_rotation_a = 0;

	m_v_x = 0;
	m_a_x = 0;

	m_v_y = 0;
	m_a_y = 0;

	m_max_rotation_v = 0;
	m_max_v = 0;
	m_max_a = 0;
}

DynamicObject::DynamicObject(const Position &p, float rotation)
{
	m_position = p;
	m_rotation = rotation;
	
	m_rotation_v = 0;
	m_rotation_a = 0;

	m_v_x = 0;
	m_a_x = 0;

	m_v_y = 0;
	m_a_y = 0;

	m_max_rotation_v = 0;
	m_max_v = 0;
	m_max_a = 0;
}

DynamicObject::DynamicObject(const DynamicObject &obj)
{
	m_position = obj.m_position;
	m_rotation = obj.m_rotation;

	m_rotation_v = obj.m_rotation_v;
	m_rotation_a = obj.m_rotation_a;

	m_v_x = obj.m_v_x;
	m_a_x = obj.m_a_x;

	m_v_y = obj.m_v_y;
	m_a_y = obj.m_a_y;

	m_max_rotation_v = obj.m_max_rotation_v;
	m_max_v = obj.m_max_v;
	m_max_a = obj.m_max_a;
}

void DynamicObject::setPosition(const Position &pos)
{
	m_position = pos;
}

void DynamicObject::setV(float v)
{
	m_v_x = v;
}

Position DynamicObject::getPosition() const
{
	return m_position;
}

float DynamicObject::getRotation() const
{
	return m_rotation;
}

float DynamicObject::getV() const
{
	return sqrt(m_v_x * m_v_x + m_v_y * m_v_y);
}

float DynamicObject::getMV() const
{
	return m_max_v;
}

float DynamicObject::getVX() const
{
	return m_v_x;
}

float DynamicObject::getVY() const
{
	return m_v_y;
}

float DynamicObject::getR(const DynamicObject &target, float ammo_speed) const
{
	Position diff = m_position - target.m_position;
	double dvx = target.m_v_x - m_v_x, dvy = target.m_v_y - m_v_y;
	double dv = sqrt(dvx * dvx + dvy * dvy), dir = ATAN2(dvx, dvy);
	diff.rotate(-dir);

	double dx = diff.x, dy = diff.y;
	double v1 = ammo_speed, v2 = dv;

	double a = v1 * v1 - v2 * v2;
	double b = 2 * v2 * dx;
	double c = -dx * dx - dy * dy;

	QuadraticEquation que = QuadraticEquation(a, b, c);
	QEResults result = que.getResult();

	float time = 0;

	if (result.resultsNumber == 1)
	{
		if (result.x1 >= 0)
			time = result.x1;
	}
	else if (result.resultsNumber == 2)
	{
		if (result.x1 >= 0)
			time = result.x1;
		else if (result.x2 >= 0)
			time = result.x2;
	}

	Position newpos = target.m_position + Position(dvx * time, dvy * time);

	return m_position.direction(newpos);
}