#include"Ammo.h"

Ammo::Ammo()
	:Ammo(AmmoType::Laser, {0, 0}, 0, 0, 0, nullptr)
{
	;
}

Ammo::Ammo(const AmmoType &at)
{
	m_group = nullptr;
	m_ammo_type = at;
	m_position = Position(0, 0);
	m_a_x = 0;
	m_v_x = 0;
	m_a_y = 0;
	m_v_y = 0;
	m_rotation = 0;
	m_rotation_v = 0;

	switch (at)
	{
	case AmmoType::Laser:
		m_max_v = 800;

		m_shield_damage = 30;
		m_armor_damage = 10;

		m_time = 5;

		break;
	case AmmoType::Rocket:
		m_max_v = 400;

		m_shield_damage = 10;
		m_armor_damage = 30;

		m_time = 3;

		break;
	}
}

Ammo::Ammo(const AmmoType &at, const Position &p, float rotation, float vx, float vy, UnitsGroup *group)
{
	m_group = group;
	m_ammo_type = at;
	m_position = p;
	m_a_x = 0;
	m_a_y = 0;
	m_rotation_v = 0;

	switch (at)
	{
	case AmmoType::Laser:
		m_max_v = 800;

		m_shield_damage = 30;
		m_armor_damage = 10;

		m_time = 5;

		break;
	case AmmoType::Rocket:
		m_max_v = 400;

		m_shield_damage = 30;
		m_armor_damage = 10;

		m_time = 3;

		break;
	}

	m_v_x = COS(rotation) * m_max_v + vx;
	m_v_y = SIN(rotation) * m_max_v + vy;
	
	m_rotation = ATAN2(m_v_x, m_v_y);
}

Ammo::Ammo(const Ammo &a)
	:DynamicObject(a)
{
	m_ammo_type = a.m_ammo_type;

	m_shield_damage = a.m_shield_damage;
	m_armor_damage = a.m_armor_damage;
}

Ammo::~Ammo()
{
	;
}

/*
void Ammo::operator=(const Ammo &a)
{
	m_ammo_type = a.m_ammo_type;

	m_position = a.m_position;
	m_rotation = a.m_rotation;

	m_v_x = a.m_v_x;
	m_v_y = a.m_v_y;

	m_max_v = a.m_max_v;

	m_shield_damage = a.m_shield_damage;
	m_armor_damage = a.m_armor_damage;
}
*/

void Ammo::setGroup(UnitsGroup *group)
{
	m_group = group;
}

void Ammo::setV(float vx, float vy)
{
	m_v_x = vx;
	m_v_y = vy;
	//m_max_v = sqrt(vx * vx + vy * vy);
	m_rotation = ATAN2(m_v_x, m_v_y);
}

void Ammo::setV(float vx, float vy, float rotation)
{
	m_rotation = rotation;
	m_v_x = COS(rotation) * m_max_v + vx;
	m_v_y = SIN(rotation) * m_max_v + vy;
	//m_max_v = sqrt(vx * vx + vy * vy);
}

bool Ammo::move(float time)
{
	if (m_time < time)
	{
		float sec = m_time;
		m_position += Position(m_v_x * sec, m_v_y * sec);

		return false;
	}
	else
	{
		m_time -= time;
		m_position += Position(m_v_x * time, m_v_y * time);

		return true;
	}
}

UnitsGroup* Ammo::getGroup() const
{
	return m_group;
}

void Ammo::draw(sf::RenderWindow &window, const Camera &camera) const
{
	camera.getOnScreenCircle(Circle(m_position, 5)).draw(window, sf::Color::Red);
	//Circle(camera.getOnScreenPos(m_position), 10).draw(window, sf::Color::Red);
}