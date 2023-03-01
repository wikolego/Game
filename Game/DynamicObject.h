#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#define _USE_MATH_DEFINES

#include<cmath>
#include<iostream>

#include"Position.h"
#include"QuadraticEquation.h"

class DynamicObject
{
protected:
	Position m_position;
	float m_rotation;

	float m_rotation_v;
	float m_rotation_a;

	float m_v_x;
	float m_a_x;

	float m_v_y;
	float m_a_y;

	float m_max_rotation_v;
	float m_max_v;
	float m_max_a;
public:
	DynamicObject();
	DynamicObject(const Position &p, float rotation);
	DynamicObject(const DynamicObject &obj);
	void setPosition(const Position &pos);
	void setV(float v);
	Position getPosition() const;
	float getRotation() const;
	float getV() const;
	float getMV() const;
	float getVX() const;
	float getVY() const;
	float getR(const DynamicObject &target, float ammo_speed) const;
};

#endif