#include"Camera.h"
#include"Item.h"

Item::Item(Position p, ItemType type)
	: DynamicObject(p, 0)
{
	m_type = type;
	m_min_distance = 15;
}

ItemType Item::getItemType() const
{
	return m_type;
}

float Item::getMinDistance() const
{
	return m_min_distance;
}

void Item::draw(sf::RenderWindow &window, const Camera &camera) const
{
	Circle(camera.getOnScreenPos(m_position), m_min_distance).draw(window, sf::Color(255, 127, 0));
}