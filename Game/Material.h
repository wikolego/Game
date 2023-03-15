#ifndef MATERIAL_H
#define MATERIAL_H

#include"Item.h"

#define MaterialsCount 5

enum MaterialType
{
	Scrap,
	Coopper,
	Iron,
	Titan,
	Diamond,
	NONE
};

class Material : public Item
{
	MaterialType m_material_type;
public:
	Material(Position p, MaterialType type, int quantity = 1);
	MaterialType getMaterialType() const;
	void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif