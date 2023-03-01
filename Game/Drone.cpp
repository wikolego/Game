#include"Drone.h"

Drone::Drone()
	: Unit({ { 0, 0 }, 0 })
{
	m_unit_type = UnitType::Drone;

	m_type = DroneType::NONE;
}

Drone::Drone(const Position &pos, float rotation, DroneType type)
	: Unit({ pos, rotation })
{
	m_unit_type = UnitType::Drone;

	m_type = type;
}

Drone::Drone(const Position &pos, float rotation, DroneType type, const Tab<sf::Texture*> *textures)
	: Unit({ pos, rotation })
{
	m_unit_type = UnitType::Drone;

	m_type = type;

	switch (m_type)
	{
	case DroneType::SHIELD1:

		m_shapes.addElement(new Ellipse(0, 0, 1.5 * 13));
		m_shapes.addElement(new Ellipse(0, 0, 13, 13));

		setArmorAndShield(15, 25, 5, 5);

		m_texture = textures->getElement((size_t)Textures::DRONE2);
		m_texture_position = Position(-13, -13);

		break;
	case DroneType::DEFENCE1:

		m_shapes.addElement(new Ellipse(0, 0, 1.5 * 13));
		m_shapes.addElement(new Ellipse(0, 0, 13, 13));

		setArmorAndShield(15, 0, 5, 5);

		m_texture = textures->getElement((size_t)Textures::DRONE2);
		m_texture_position = Position(-13, -13);

		break;
	case DroneType::ATTACK1:

		m_shapes.addElement(new Ellipse(0, 0, 1.5 * 10));
		m_shapes.addElement(new Rectangle(-10, -10, 20, 20));

		setArmorAndShield(30, 25, 5, 5);

		m_texture = textures->getElement((size_t)Textures::DRONE3);
		m_texture_position = Position(-10, -16.5);

		break;
	case DroneType::ATTACK2:

		m_shapes.addElement(new Ellipse(0, 0, 1.5 * 10));
		m_shapes.addElement(new Rectangle(-10, -10, 20, 20));

		setArmorAndShield(30, 25, 5, 5);

		m_texture = textures->getElement((size_t)Textures::DRONE1);
		m_texture_position = Position(-10, -10);

		break;
	}
}

Drone::~Drone()
{
	for (int i = 0; i < m_shapes.getSize(); i++)
		delete m_shapes.getElement(i);
	//printf("Drone\n");
}

DroneType Drone::getType() const
{
	return m_type;
}

void Drone::draw(sf::RenderWindow &window, const Camera &camera) const
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