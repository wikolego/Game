#include"Inventory.h"

Inventory::Inventory()
{
	for (int i = 0; i < MaterialsCount; i++)
		m_materials[i] = 0;

	m_subsystems_count = 0;
	m_subsystems_max_count = 3;
	m_subsystems = new SubsystemType[m_subsystems_max_count];

	m_weight = 0;
	m_max_weight = 100;

	m_space = 0;
	m_max_space = 100;
}

Inventory::~Inventory()
{
	delete[] m_subsystems;
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
	case Item::Material:
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
	}
	break;
	case Item::Weapon:
	{

	}
	break;
	case Item::Subsystem:
	{
		Subsystem *sys = (Subsystem*)item;

		if (m_subsystems_count >= m_subsystems_max_count)
			return 0;

		if (contains(sys->getSubsystemType()))
			return 0;

		m_subsystems[m_subsystems_count++] = sys->getSubsystemType();

		return 2;
	}
	break;
	}
	return 0;
}

bool Inventory::contains(SubsystemType subsystem)
{
	for (int i = 0; i < m_subsystems_count; i++)
	{
		if (m_subsystems[i] == subsystem)
			return true;
	}
	return false;
}

int Inventory::getCountOf(MaterialType mat) const
{
	return m_materials[mat];
}