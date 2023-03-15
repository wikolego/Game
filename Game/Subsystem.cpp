#include"Camera.h"
#include"Subsystem.h"

Subsystem::Subsystem(Position p, SubsystemType type, int quantity)
	: Item(p, Item::Subsystem, quantity)
{
	m_subsystem_type = type;
	m_item_values = &itemValues[m_item_type][(int)m_subsystem_type];
}

SubsystemType Subsystem::getSubsystemType() const
{
	return m_subsystem_type;
}

void Subsystem::draw(sf::RenderWindow &window, const Camera &camera) const
{
	Circle(camera.getOnScreenPos(m_position), m_item_values->pick_up_range).draw(window, sf::Color(0, 0, 128 + 60 * (int)m_subsystem_type));
}