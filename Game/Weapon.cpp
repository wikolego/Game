#include"Weapon.h"

Weapon::Weapon()
	: Weapon(WeaponType::Laser1)
{
	;
}

Weapon::Weapon(WeaponType wt)
	: Weapon({ 0, 0 }, 0, wt)
{
	;
}

Weapon::Weapon(const Position &pos, float rotation, WeaponType wt)
{
	m_position = pos;
	m_rotation = rotation;

	m_weapon_type = wt;
	m_time = 0;
	m_ready_to_shoot = false;

	switch (m_weapon_type)
	{
	case WeaponType::Laser1:
		m_shield_damage = 30;
		m_armor_damage = 10;

		m_time_to_shoot = 0.5;

		m_accuracy = 1;

		m_energy = 15;

		break;
	case WeaponType::Laser2:
		m_shield_damage = 20;
		m_armor_damage = 20;

		m_time_to_shoot = 1;

		m_accuracy = 10;

		m_energy = 15;

		break;
	case WeaponType::Cannon1:
		m_shield_damage = 10;
		m_armor_damage = 30;

		m_time_to_shoot = 1;

		m_accuracy = 1;

		m_energy = 15;

		break;
	}
}

Weapon::Weapon(const Weapon &wp)
{
	m_weapon_type = wp.m_weapon_type;

	m_time = wp.m_time;

	m_time_to_shoot = wp.m_time_to_shoot;

	m_ready_to_shoot = wp.m_ready_to_shoot;

	m_shield_damage = wp.m_shield_damage;
	m_armor_damage = wp.m_armor_damage;

	m_accuracy = wp.m_accuracy;

	m_energy = wp.m_energy;

	m_rotation = wp.m_rotation;

	m_position = wp.m_position;

	printf("Trzeba uzupelnic konstruktor z const Weapon\n");
}

void Weapon::operator=(const Weapon &wp)
{
	m_weapon_type = wp.m_weapon_type;

	m_time = wp.m_time;

	m_time_to_shoot = wp.m_time_to_shoot;

	m_ready_to_shoot = wp.m_ready_to_shoot;

	m_shield_damage = wp.m_shield_damage;
	m_armor_damage = wp.m_armor_damage;

	m_accuracy = wp.m_accuracy;

	m_energy = wp.m_energy;

	printf("Trzeba uzupelnic operator= w Weapon\n");
}

void Weapon::setPosition(const Position &p)
{
	m_position = p;
}

void Weapon::setRotation(float rotation)
{
	m_rotation = rotation;
	m_shape->setRotation(rotation);
}

void Weapon::setTimeToShoot(float time)
{
	m_time_to_shoot = time;
	m_ready_to_shoot = time > m_time_to_shoot;
}

void Weapon::setTime(float time)
{
	m_time = time;
}

void Weapon::setTexture(sf::Texture *texture, const sf::IntRect &rect)
{
	m_shape->setTexture(texture);
	m_shape->setTextureRect(rect);
}

Position Weapon::getPosition() const
{
	return m_position;
}

float Weapon::getRotation() const
{
	return m_rotation;
}

float Weapon::getEnergy() const
{
	return m_energy;
}

float Weapon::getAccuracy() const
{
	return m_accuracy;
}

float Weapon::getTimeToShoot() const
{
	return m_time_to_shoot;
}

float Weapon::getTime() const
{
	return m_time;
}

sf::RectangleShape* Weapon::getShape() const
{
	return m_shape;
}

void Weapon::reset()
{
	m_time = 0;
	m_ready_to_shoot = false;
}

void Weapon::updateTime(float time)
{
	m_time += time;

	if (m_time >= m_time_to_shoot)
		m_ready_to_shoot = true;
}

void Weapon::notShoot(float time)
{
	m_time = 0;
}

void Weapon::draw(sf::RenderWindow &window, const Camera &camera)
{
	Position pos = camera.getOnScreenPos(m_position);
	m_shape->setPosition(pos.x, pos.y);
}

void Weapon::draw(sf::RenderWindow &window)
{
	;
}