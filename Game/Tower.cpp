#include"Tower.h"

Tower::Tower()
	: Unit({ { 0, 0 } , 0})
{
	m_unit_type = UnitType::Tower;
	m_tower_type = TowerType::NONE;
	m_weapon = nullptr;
}

Tower::Tower(const Position &p, float rotation)
	: Unit({p, rotation})
{
	m_unit_type = UnitType::Tower;
	m_tower_type = TowerType::NONE;
	m_weapon = nullptr;
}

Tower::Tower(const Position &p, float rotation, const TowerType &type, const Tab<sf::Texture*> *textures)
	: Unit({ p, rotation })
{
	m_rotation_v = 45;

	m_unit_type = UnitType::Tower;

	m_tower_type = type;

	switch (type)
	{
	case TowerType::DefenceTower1:
		m_weapon = new Laser1({ 0 , 0 }, 0);
		m_weapon->setTimeToShoot(m_weapon->getTimeToShoot() * 3);
		
		m_shapes.addElement(new Ellipse(0, 0, 1.5 * 13));
		m_shapes.addElement(new Ellipse(0, 0, 13, 13));

		setArmorAndShield(50, 0, 0, 0);

		m_texture = textures->getElement((size_t)Textures::DRONE2);
		m_texture_position = Position(-13, -13);
		break;
	case TowerType::Tower2:
		
		break;
	case TowerType::NONE:
		m_weapon = nullptr;
		break;
	}
}

Tower::~Tower()
{
	delete m_weapon;
	for (int i = 0; i < m_shapes.getSize(); i++)
		delete m_shapes.getElement(i);
}

void Tower::setTarget(Unit *target)
{
	if (target != nullptr)
	{
		if (target == this)
			m_target = nullptr;
		else if (target->getGroup() != m_group)
			m_target = target;
	}
	else
		m_target = nullptr;
}

Unit* Tower::getTarget() const
{
	return m_target;
}

TowerType Tower::getType() const
{
	return m_tower_type;
}

void Tower::draw(sf::RenderWindow &window, const Camera &camera) const
{
	Position draw_pos = m_position + m_texture_position;
	draw_pos.rotate(m_position, m_rotation + 90);

	Rectangle rect2 = camera.getOnScreenRect(Rectangle(draw_pos, Position(m_texture->getSize().x, m_texture->getSize().y), m_rotation + 90), 0);

	sf::RectangleShape rect;
	rect.setTexture(m_texture);
	rect.setSize({ rect2.w, rect2.h });
	rect.setPosition(rect2.x, rect2.y);
	rect.setRotation(rect2.rotation);
	window.draw(rect);

	Ellipse elp = *(Ellipse*)m_shapes.getElement(0);

	Position p = elp.getPosition();
	p.rotate(m_rotation);
	elp.setPosition(p + m_position);
	elp.rotate(m_rotation);

	camera.getOnScreenEllipse(elp).draw(window, sf::Color(0, 0, 255, getShieldAsF() * 127));

	window.draw(rect);
}