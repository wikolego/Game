#include"Camera.h"
#include"Items.h"

void itemValuesInit()
{
	itemValues = new ItemValues*[ItemsCount];

	itemValues[0] = new ItemValues[MaterialsCount];
	itemValues[0][Scrap] = ItemValues(15, 1, 1, 1);
	itemValues[0][Coopper] = ItemValues(15, 1, 1, 1);
	itemValues[0][Iron] = ItemValues(15, 1, 1, 1);
	itemValues[0][Titan] = ItemValues(15, 1, 1, 1);
	itemValues[0][Diamond] = ItemValues(15, 1, 1, 1);

	itemValues[1] = new ItemValues[1];
	itemValues[1][0] = ItemValues(15, 1, 1, 1);

	itemValues[2] = new ItemValues[1];
	itemValues[2][0] = ItemValues(15, 1, 1, 1);
	
}

void itemValuesDelete()
{
	for (int i = 0; i < ItemsCount; i++)
		delete[] itemValues[i];
	delete[] itemValues;
}

Item::Item(Position p, ItemType type, int quantity)
	: DynamicObject(p, 0)
{
	m_type = type;
	m_quantity = quantity;
}

ItemType Item::getItemType() const
{
	return m_type;
}

ItemValues Item::getItemValues() const
{
	return *m_item_values;
}

int Item::getQuantity() const
{
	return m_quantity;
}

float Item::getPickUpRange() const
{
	return m_item_values->pick_up_range;
}

float Item::getInventorySpace() const
{
	return m_item_values->inventory_space;
}

float Item::getWeight() const
{
	return m_item_values->weight;
}

float Item::getPrice() const
{
	return m_item_values->price;
}

void Item::draw(sf::RenderWindow &window, const Camera &camera) const
{
	Circle(camera.getOnScreenPos(m_position), m_item_values->pick_up_range).draw(window, sf::Color(255, 127, 0));
}