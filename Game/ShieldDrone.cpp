#include"ShieldDrone.h"

ShieldDrone::ShieldDrone()
	: Drone({ 0, 0 }, 0, DroneType::SHIELD1)
{
	
}

ShieldDrone::ShieldDrone(const Position &pos, float rotation, const Tab<sf::Texture*> *textures)
	: Drone(pos, rotation, DroneType::SHIELD1, textures)
{
	
}

void ShieldDrone::update(float time, SnakeTab<Ammo*> *ammoTab)
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

/*
void ShieldDrone::draw(sf::RenderWindow &window, const Camera &camera) const
{
	sf::RectangleShape rect;

	Position draw_pos = m_position + m_texture_position;
	draw_pos.rotate(m_position, m_rotation);

	draw_pos = camera.getOnScreenPos(draw_pos);

	rect.setPosition(draw_pos.x, draw_pos.y);
	rect.setRotation(m_rotation - camera.getRectangle().rotation);

	float scale = camera.getScale();

	sf::Vector2u vec = m_texture->getSize();

	rect.setSize({ vec.x * scale, vec.y * scale });
	rect.setTexture(m_texture);

	window.draw(rect);
}
*/