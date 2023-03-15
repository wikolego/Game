#ifndef ITEM_H
#define ITEM_H

#define _USE_MATH_DEFINES

#include<SFML/Graphics.hpp>

#include"DynamicObject.h"

extern class Camera;

#define ItemsCount 3

/*
enum class ItemType
{
	Material,
	Weapon,
	Subsystem
};
*/

struct ItemValues
{
	float pick_up_range;
	float inventory_space;
	float weight;
	float price;

	ItemValues()
	{
		pick_up_range = 0;
		inventory_space = 0;
		weight = 0;
		price = 0;
	}
	ItemValues(float range, float inv_space, float wght, float prc)
	{
		pick_up_range = range;
		inventory_space = inv_space;
		weight = wght;
		price = prc;
	}
	ItemValues(const ItemValues &cp)
	{
		pick_up_range = cp.pick_up_range;
		inventory_space = cp.inventory_space;
		weight = cp.weight;
		price = cp.price;
	}
	void operator=(const ItemValues &cp)
	{
		pick_up_range = cp.pick_up_range;
		inventory_space = cp.inventory_space;
		weight = cp.weight;
		price = cp.price;
	}
};

extern ItemValues **itemValues;
void itemValuesInit();
void itemValuesDelete();

class Item : public DynamicObject
{
public:
	enum Type
	{
		Material,
		Weapon,
		Subsystem,
		NONE
	};

protected:
	Type m_item_type;

	int m_quantity;
	const ItemValues *m_item_values;

public:
	Item(Position p, Type type, int quantity = 1);
	Type getItemType() const;
	ItemValues getItemValues() const;
	int getQuantity() const;
	float getPickUpRange() const;
	float getInventorySpace() const;
	float getWeight() const;
	float getPrice() const;
	virtual void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif