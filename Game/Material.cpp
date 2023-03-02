#include"Camera.h"
#include"Material.h"

Material::Material(Position p, MaterialType type, int quantity)
	: Item(p, ItemType::Material, quantity)
{
	m_material_type = type;
	m_item_values = &itemValues[(int)m_type][(int)m_material_type];
}

MaterialType Material::getMaterialType() const
{
	return m_material_type;
}

void Material::draw(sf::RenderWindow &window, const Camera &camera) const
{
	Circle(camera.getOnScreenPos(m_position), m_item_values->pick_up_range).draw(window, sf::Color(60 * (int)m_material_type, 127, 0));
}