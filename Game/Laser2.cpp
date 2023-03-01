#include"Laser2.h"

Laser2::Laser2()
	:Weapon(WeaponType::Laser2)
{
	m_time = m_time_to_shoot;
	m_ready_to_shoot = true;
}

Laser2::Laser2(float time)
	:Weapon(WeaponType::Laser2)
{
	m_time = time;
	if (m_time >= m_time_to_shoot)
		m_ready_to_shoot = true;
	else
		m_ready_to_shoot = false;
}

Laser2::Laser2(const Position &pos, float rotation)
	:Weapon(pos, rotation, WeaponType::Laser2)
{
	m_time = m_time_to_shoot;
	m_ready_to_shoot = true;
}

void Laser2::notShoot(float time)
{
	if (m_time > m_time_to_shoot)
		m_time = m_time_to_shoot;
}

Ammo* Laser2::shoot()
{
	if (m_ready_to_shoot == true)
	{
		//m_time -= m_time_to_shoot;
		m_time = 0;
		m_ready_to_shoot = false;

		//printf("One shot\n");

		Ammo *ammo = new Ammo(AmmoType::Laser);

		return ammo;
	}
	return nullptr;
}