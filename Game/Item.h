#ifndef ITEM_H
#define ITEM_H

#define _USE_MATH_DEFINES

#include<SFML/Graphics.hpp>

#include"DynamicObject.h"

extern class Camera;

enum class ItemType
{
	Material,
	Weapon,
	Subsystem,
	NONE
};

class Item : public DynamicObject
{
	ItemType m_type;

	float m_min_distance;

public:
	Item(Position p, ItemType type);
	ItemType getItemType() const;
	float getMinDistance() const;
	virtual void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif