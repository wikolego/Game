#include"Laser1.h"

Laser1::Laser1()
	:Weapon(WeaponType::Laser1)
{
	m_time = m_time_to_shoot;
	m_ready_to_shoot = true;
}

Laser1::Laser1(float time)
	:Weapon(WeaponType::Laser1)
{
	m_time = time;
	if (m_time >= m_time_to_shoot)
		m_ready_to_shoot = true;
	else
		m_ready_to_shoot = false;
}

Laser1::Laser1(const Position &pos, float rotation)
	:Weapon(pos, rotation, WeaponType::Laser1)
{
	m_time = m_time_to_shoot;
	m_ready_to_shoot = true;
}

void Laser1::notShoot(float time)
{
	if (m_time > m_time_to_shoot)
		m_time = m_time_to_shoot;
}

Ammo* Laser1::shoot()
{
	if (m_ready_to_shoot == true)
	{
		m_time = 0;
		m_ready_to_shoot = false;

		//printf("One shot\n");

		Ammo *ammo = new Ammo(AmmoType::Laser);
		
		return ammo;
	}
	return nullptr;
}