#include"Inventory.h"

Inventory::Inventory()
{
	for (int i = 0; i < MaterialsCount; i++)
		m_materials[i] = 0;

	m_weight = 0;
	m_max_weight = 100;

	m_space = 0;
	m_max_space = 100;
}

Inventory::~Inventory()
{

}

bool Inventory::changeCountOf(MaterialType mat, int val)
{
	m_materials[mat] += val;
	return true;
}

int Inventory::addItem(Item *item)
{
	switch (item->getItemType())
	{
	case ItemType::Material:
	{
		//*
		Material *mat = (Material*)item;
		int tp = (int)mat->getMaterialType();

		m_materials[tp] += mat->getQuantity();
		m_weight += mat->getWeight();
		m_space += mat->getInventorySpace();

		/*
		printf("Materials:\n");
		for (int i = 0; i < MaterialsCount; i++)
			printf("%d - %d\n", i, m_materials[i]);
		printf("\n");
		*/

		return 2;
		//*/

		return 2;
	}
	break;
	}
	return 0;
}

int Inventory::getCountOf(MaterialType mat) const
{
	return m_materials[mat];
}