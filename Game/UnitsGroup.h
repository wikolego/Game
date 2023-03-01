#ifndef UNITSGROUP_H
#define UNITSGROUP_H

#include"Tab.h"
#include"Unit.h"

enum class GroupType
{
	COLONIAL,
	REBEL,
	PIRATE,
	NONE
};

class UnitsGroup
{
	GroupType m_type;
	Unit *m_main_unit;
	Tab<Unit*> *m_units;
public:
	UnitsGroup();
	UnitsGroup(GroupType type, Unit *main_unit);
	~UnitsGroup();
	bool addUnit(Unit *unit);
	bool removeUnit(size_t indeks);
	bool removeUnit(Unit *unit);
	Unit* getMainUnit() const;
	Unit* getUnit(size_t indeks) const;
	size_t getSize() const;
	GroupType getType() const;
	bool containsUnit(const Unit *unit) const;
	void print(const char *s = "") const;
};

#endif