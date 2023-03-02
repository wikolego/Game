#ifndef INVENTORY_H
#define INVENTORY_H

#include"Items.h"

class Inventory
{
	int m_materials[MaterialsCount];

	int m_weight;
	int m_max_weight;

	int m_space;
	int m_max_space;
public:
	Inventory();
	~Inventory();
	bool changeCountOf(MaterialType mat, int val);
	int addItem(Item *item); // returns 0 - we can't take anything; 1 - taken, but not all, 2 - taken all
	int getCountOf(MaterialType mat) const;
};

#endif