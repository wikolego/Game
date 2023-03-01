#include"Cannon1.h"

Cannon1::Cannon1()
	:Weapon(WeaponType::Cannon1)
{
	m_time = m_time_to_shoot;
	m_ready_to_shoot = true;
}

Cannon1::Cannon1(float time)
	:Weapon(WeaponType::Cannon1)
{
	m_time = time;
	if (m_time >= m_time_to_shoot)
		m_ready_to_shoot = true;
	else
		m_ready_to_shoot = false;
}

Cannon1::Cannon1(const Position &pos, float rotation)
	:Weapon(pos, rotation, WeaponType::Cannon1)
{
	m_time = m_time_to_shoot;
	m_ready_to_shoot = true;
}

void Cannon1::notShoot(float time)
{
	if (m_time > m_time_to_shoot)
		m_time = m_time_to_shoot;
}

Ammo* Cannon1::shoot()
{
	if (m_ready_to_shoot == true)
	{
		m_time = 0;
		m_ready_to_shoot = false;

		Ammo *ammo = new Ammo(AmmoType::Rocket);

		return ammo;
	}
	return nullptr;
}