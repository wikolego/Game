#include"DefenceTower1.h"

DefenceTower1::DefenceTower1(const Position &pos, float rotation, const Tab<sf::Texture*> *textures)
	: Tower(pos, rotation, TowerType::DefenceTower1, textures)
{

}

void DefenceTower1::update(float time, SnakeTab<Ammo*> *ammoTab)
{
	if (m_group != nullptr)
	{
		if (m_target != nullptr)
		{
			float to_rot = getR(*m_target, 800);
			float rot_diff = rotation_difference(m_rotation, to_rot);
			float rot_change = m_rotation_v * time;

			bool shoot = (rot_diff == 0);

			if (rot_diff < 0)
			{
				if (-rot_diff <= rot_change)
				{
					shoot = true;
					m_rotation = to_rot;
				}
				else
					m_rotation = fixRotation(m_rotation + rot_change);
			}
			else if (rot_diff > 0)
			{
				if (rot_diff <= rot_change)
				{
					shoot = true;
					m_rotation = to_rot;
				}
				else
					m_rotation = fixRotation(m_rotation - rot_change);
			}

			//printf("%d\n", shoot);

			m_weapon->updateTime(time);
			if (shoot)
			{
				Ammo *ammo = m_weapon->shoot();
				if (ammo != nullptr)
				{
					ammo->setGroup(m_group);
					ammo->setPosition(getRelativePosition(m_weapon->getPosition()));
					ammo->setV(m_v_x, m_v_y, m_rotation + m_weapon->getRotation());
					ammoTab->add(ammo);
				}
			}
		}
		else
		{
			m_weapon->reset();
		}
	}
}