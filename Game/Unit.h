#ifndef UNIT_H
#define UNIT_H

#include"DynamicObject.h"
#include"Shapes.h"
#include"SnakeTab.h"
#include"MathFunctions.h"

enum class Textures
{
	SHIP1,
	SHIP2,
	SHIP3,
	DRONE1,
	DRONE2,
	DRONE3,
	DRONE4,
	SIZE
};

enum class UnitType
{
	Ship,
	Drone,
	Tower,
	NONE
};

class Ammo;
class UnitsGroup;

class Unit : public DynamicObject
{
	friend class UnitsGroup;
protected:
	UnitType m_unit_type;

	UnitsGroup *m_group;

	Tab<Shape*> m_shapes;

	float m_armor;
	float m_max_armor;

	float m_shield;
	float m_max_shield;
	float m_shield_rengeneration;
	float m_shield_cooldown_time;

	float m_time_after_hited;

	int m_slowed;
public:
	Unit();
	Unit(const DynamicObject &obj);
	Unit(float max_arm, float max_sh, float sh_reg, float sh_cool);
	Unit(const DynamicObject &obj, float max_arm, float max_sh, float sh_reg, float sh_cool);
	virtual ~Unit();
	void setGroup(UnitsGroup *group);
	void setArmorAndShield(float max_arm, float max_sh, float sh_reg, float sh_cool);
	void setShield(float sh);
	virtual void updateByDmg(float arm, float sh);
	virtual void updateShield(float time);
	void changeSlowed(int slowed = 1);
	void incraseShield(float sh);
	virtual bool isTouching(SnakeTab<Ammo*> *ammoTab, float time);
	//virtual void getItems();
	UnitsGroup* getGroup() const;
	UnitType getUnitType() const;
	float getArmor() const;
	float getArmorAsF() const;
	float getMaxArmor() const;
	float getShield() const;
	float getShieldAsF() const;
	float getMaxShield() const;
	int getSlowed() const;
	Position getRelativePosition(Position p) const;
};

#endif