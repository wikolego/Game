#ifndef INVENTORY_H
#define INVENTORY_H

#include"Items.h"

class Inventory
{
	int m_materials[MaterialsCount];

	SubsystemType *m_subsystems;
	int m_subsystems_count;
	int m_subsystems_max_count;

	int m_weight;
	int m_max_weight;

	int m_space;
	int m_max_space;
public:
	Inventory();
	~Inventory();
	bool changeCountOf(MaterialType mat, int val);
	int addItem(Item *item); // returns 0 - we can't take anything; 1 - taken, but not all, 2 - taken all
	bool contains(SubsystemType subsystem);
	int getCountOf(MaterialType mat) const;
};

#endif