#include"Ammo.h"

Unit::Unit()
{
	m_unit_type = UnitType::NONE;

	m_armor = 0;
	m_max_armor = 0;

	m_shield = 0;
	m_max_shield = 0;
	m_shield_rengeneration = 0;
	m_shield_cooldown_time = 0;

	m_time_after_hited = 0;

	m_slowed = false;
}

Unit::Unit(const DynamicObject &obj)
	: DynamicObject(obj)
{
	m_unit_type = UnitType::NONE;

	m_armor = 0;
	m_max_armor = 0;

	m_shield = 0;
	m_max_shield = 0;
	m_shield_rengeneration = 0;
	m_shield_cooldown_time = 0;

	m_time_after_hited = 0;

	m_slowed = false;
}

Unit::Unit(float max_arm, float max_sh, float sh_reg, float sh_cool)
{
	m_unit_type = UnitType::NONE;

	m_armor = max_arm;
	m_max_armor = max_arm;

	m_shield = max_sh;
	m_max_shield = max_sh;
	m_shield_rengeneration = sh_reg;
	m_shield_cooldown_time = sh_cool;

	m_time_after_hited = sh_cool;

	m_slowed = false;
}

Unit::Unit(const DynamicObject &obj, float max_arm, float max_sh, float sh_reg, float sh_cool)
	: DynamicObject(obj)
{
	m_unit_type = UnitType::NONE;

	m_armor = max_arm;
	m_max_armor = max_arm;

	m_shield = max_sh;
	m_max_shield = max_sh;
	m_shield_rengeneration = sh_reg;
	m_shield_cooldown_time = sh_cool;

	m_time_after_hited = sh_cool;

	m_slowed = false;
}

Unit::~Unit()
{
	;
}

void Unit::setGroup(UnitsGroup *group)
{
	group->addUnit(this);
}

void Unit::setArmorAndShield(float max_arm, float max_sh, float sh_reg, float sh_cool)
{
	m_armor = max_arm;
	m_max_armor = max_arm;

	m_shield = max_sh;
	m_max_shield = max_sh;
	m_shield_rengeneration = sh_reg;
	m_shield_cooldown_time = sh_cool;

	m_time_after_hited = sh_cool;
}

void Unit::setShield(float sh)
{
	m_shield = sh;
}

void Unit::changeSlowed(int slowed)
{
	m_slowed += slowed;
}

void Unit::updateByDmg(float arm, float sh)
{
	m_time_after_hited = 0;

	if (m_shield > 0)
	{
		if (sh <= m_shield)
			m_shield -= sh;
		else
		{
			m_shield = 0;
			float new_arm_dmg = (sh - m_shield) / sh * arm;
			m_armor -= new_arm_dmg;
		}
	}
	else
	{
		m_armor -= arm;
	}
}

void Unit::updateShield(float time)
{
	m_time_after_hited += time;
	if (m_time_after_hited >= m_shield_cooldown_time)
	{
		m_time_after_hited = m_shield_cooldown_time;
		incraseShield(time * m_shield_rengeneration);
	}
}

void Unit::incraseShield(float sh)
{
	m_shield += sh;
	if (m_shield > m_max_shield)
		m_shield = m_max_shield;
}

bool Unit::isTouching(SnakeTab<Ammo*> *ammoTab, float time)
{
	bool totally_hited = false;
	size_t i = 0;
	size_t size = 1;
	Shape *shape;

	if (m_shield <= 0)
	{
		i = 1;
		size = m_shapes.getSize();
	}

	for (; i < size; i++)
	{
		shape = m_shapes.getElement(i);
		switch (shape->type)
		{
		case ShapeType::Rectangle:
			shape = &Rectangle(*(Rectangle*)shape);
			break;
		case ShapeType::Circle:
			shape = &Circle(*(Circle*)shape);
			break;
		case ShapeType::Ellipse:
			shape = &Ellipse(*(Ellipse*)shape);
			break;
		}

		Position p = shape->getPosition();
		p.rotate(m_rotation);
		shape->setPosition(p + m_position);
		shape->rotate(m_rotation);

		//_______________________________________________________________________________________________________

		SnakeTabElement<Ammo*> *element = ammoTab->getFirst();
		SnakeTabElement<Ammo*> *next;

		while (element != nullptr)
		{
			next = element->getNext();

			Ammo *ammo = element->getContent();

			bool this_unit = ammo->m_group != nullptr ? ammo->m_group->containsUnit(this) : false;

			if (!this_unit)
			{
				bool hited = shape->posIn(ammo->getPosition());
				if (hited)
				{
					totally_hited = true;
					updateByDmg(ammo->m_armor_damage, ammo->m_shield_damage);
					delete element->getContent();
					ammoTab->remove(element);
					delete element;
				}
			}

			element = next;
		}
	}
	if (!totally_hited)
		updateShield(time);

	//printf("%f, %f\n", m_armor, m_shield);

	return m_armor <= 0;
}

UnitsGroup* Unit::getGroup() const
{
	return m_group;
}

UnitType Unit::getUnitType() const
{
	return m_unit_type;
}

float Unit::getArmor() const
{
	return m_armor;
}

float Unit::getArmorAsF() const
{
	return m_armor / m_max_armor;
}

float Unit::getMaxArmor() const
{
	return m_max_armor;
}

float Unit::getShield() const
{
	return m_shield;
}

float Unit::getShieldAsF() const
{
	if (m_max_shield == 0)
		return 0;
	return m_shield / m_max_shield;
}

float Unit::getMaxShield() const
{
	return m_max_shield;
}

int Unit::getSlowed() const
{
	return m_slowed;
}

Position Unit::getRelativePosition(Position p) const
{
	p.rotate(m_rotation);
	return p + m_position;
}