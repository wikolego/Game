#ifndef INVENTORY_H
#define INVENTORY_H

#include"Item.h"

#define MaterialsCount 3

enum MaterialType
{
	Scrap,
	Coopper,
	Diamond
};

struct InRange
{
	int min;
	int max;
	int count;
	InRange()
	{
		min = 0;
		max = 10;
		count = 0;
	}
	InRange(int mn, int mx, int ct)
	{
		min = mn;
		max = mx;
		count = ct;
	}
	/*
	void fixCount()
	{
		if (min > count)
			count = min;
		if (max < count)
			count = max;
	}
	int getWrongCount() // func returns number, if there is too much or less of it
	{
		if (min > count)
			return count - min;
		if (max < count)
			return count - max;
		return 0;
	}
	*/
};

class Inventory
{
	InRange m_materials[MaterialsCount];
public:
	Inventory();
	~Inventory();
	bool changeCountOf(MaterialType mat, int val);
	int addItem(Item *item); // returns 0 - we can't take anything; 1 - taken, but not all, 2 - taken all
	int getCountOf(MaterialType mat) const;
};

#endif