#include"AttackDrone2.h"

AttackDrone2::AttackDrone2()
	: Drone({ 0, 0 }, 0, DroneType::ATTACK2)
{
	m_target = nullptr;
}

AttackDrone2::AttackDrone2(const Position &pos, float rotation, const Tab<sf::Texture*> *textures, Unit *target)
	: Drone(pos, rotation, DroneType::ATTACK2, textures)
{
	setTarget(target);
}

void AttackDrone2::update(float time, SnakeTab<Ammo*> *ammoTab)
{
	if (m_group != nullptr)
	{
		Unit *to_unit = m_group->getMainUnit();

		Position p(-50, 20);
		p.rotate(to_unit->getRotation());
		m_v_x = to_unit->getVX();
		m_v_y = to_unit->getVY();

		m_position = to_unit->getPosition() + p;

		m_rotation = fixRotation(m_rotation - 60.0f * time);
	}
}

void AttackDrone2::setTarget(Unit *target)
{
	if (m_target != nullptr)
		m_target->changeSlowed(-1);

	if (target != this)
	{
		m_target = target;

		if (target != nullptr)
		{
			target->changeSlowed();
			//m_target->getPosition().print("\n");
		}
	}
	else
		m_target = nullptr;
}

Unit* AttackDrone2::getTarget() const
{
	return m_target;
}