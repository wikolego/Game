#include"UnitsGroup.h"

UnitsGroup::UnitsGroup()
{
	m_type = GroupType::NONE;
	m_main_unit = nullptr;
	m_units = nullptr;
}

UnitsGroup::UnitsGroup(GroupType type, Unit *main_unit)
{
	m_type = type;
	m_main_unit = main_unit;

	if (m_main_unit != nullptr)
	{
		m_units = new Tab<Unit*>(1);
		m_units->setElement(m_main_unit, 0);

		if (m_main_unit->m_group == nullptr)
			m_main_unit->m_group = this;
	}
	else
		m_units = nullptr;
}

UnitsGroup::~UnitsGroup()
{
	if (m_units != nullptr)
	{
		size_t size = m_units->getSize();

		if (size > 0)
		{
			for (size_t i = 0; i < size; i++)
				m_units->m_tab[i]->m_group = nullptr;
		}
		delete m_units;
	}
}

bool UnitsGroup::addUnit(Unit *unit)
{
	size_t size = m_units->getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (m_units->getElement(i) == unit)
			return false;
	}

	m_units->addElement(unit);
	unit->m_group = this;

	return true;
}

bool UnitsGroup::removeUnit(size_t indeks)
{
	if (indeks >= m_units->m_size)
		return false;

	if (m_units->m_tab[indeks] == m_main_unit)
		m_main_unit = nullptr;

	m_units->m_tab[indeks]->m_group = nullptr;
	m_units->removeElement(indeks);

	return true;
}

bool UnitsGroup::removeUnit(Unit *unit)
{
	for (int i = 0; i < m_units->m_size; i++)
	{
		Unit *cur = m_units->getElement(i);

		if (unit == m_units->m_tab[i])
		{
			if (unit == m_main_unit)
				m_main_unit = nullptr;

			unit->m_group = nullptr;
			m_units->removeElement(i);

			return true;
		}
	}

	return false;
}

Unit* UnitsGroup::getMainUnit() const
{
	return m_main_unit;
}

Unit* UnitsGroup::getUnit(size_t indeks) const
{
	return m_units->m_tab[indeks];
}

size_t UnitsGroup::getSize() const
{
	return m_units->m_size;
}

GroupType UnitsGroup::getType() const
{
	return m_type;
}

bool UnitsGroup::containsUnit(const Unit *unit) const
{
	for (size_t i = 0; i < m_units->m_size; i++)
	{
		if (m_units->m_tab[i] == unit)
			return true;
	}
	return false;
}

void UnitsGroup::print(const char *s) const
{
	int size = m_units->getSize();

	printf("size = %d, type = %d: ", size, m_type);

	for (int i = 0; i < size; i++)
		printf("%d, ", (int)m_units->getElement(i)->getUnitType());

	printf("%s", s);
}