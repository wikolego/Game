#include"Inventory.h"

Inventory::Inventory()
{
	m_materials[Scrap] = InRange(0, 100, 10);
	m_materials[Coopper] = InRange(0, 50, 0);
	m_materials[Diamond] = InRange(0, 10, 0);
}

Inventory::~Inventory()
{

}

bool Inventory::changeCountOf(MaterialType mat, int val)
{
	m_materials[mat].count += val;
	return true;
}

int Inventory::addItem(Item *item)
{
	switch (item->getItemType())
	{
	case ItemType::Material:
	{
		/*
		Material *mat = (Material*)item;
		int tp = (int)mat->getMaterialType();
		if (m_materials[tp].value >= m_materials[tp].max)
			return 0;
		m_materials[tp].value += mat.getCount();
		if (m_materials[tp].value <= m_materials[tp].max)
			return 2;
		else
		{
			mat.setCount(m_materials[tp].value - m_materials[tp].max);
			m_materials[tp].value = m_materials[tp].max;
			return 1;
		}
		*/

		return 2;
	}
	break;
	}
	return 0;
}

int Inventory::getCountOf(MaterialType mat) const
{
	return m_materials[mat].count;
}