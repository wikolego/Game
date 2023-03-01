#include"DefenceDrone.h"

DefenceDrone::DefenceDrone()
	: Drone({ 0, 0 }, 0, DroneType::DEFENCE1)
{

}

DefenceDrone::DefenceDrone(const Position &pos, float rotation, const Tab<sf::Texture*> *textures)
	: Drone(pos, rotation, DroneType::DEFENCE1, textures)
{
	
}

void DefenceDrone::update(float time, SnakeTab<Ammo*> *ammoTab)
{
	if (m_group != nullptr)
	{
		Unit *to_unit = m_group->getMainUnit();

		Position p(0, -40);
		p.rotate(to_unit->getRotation());
		m_v_x = to_unit->getVX();
		m_v_y = to_unit->getVY();

		m_position = to_unit->getPosition() + p;

		to_unit->incraseShield(time * 5.0f);

		m_rotation = fixRotation(m_rotation - 60.0f * time);
	}
}