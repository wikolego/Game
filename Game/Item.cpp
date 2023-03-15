#include"Camera.h"
#include"Items.h"

void itemValuesInit()
{
	itemValues = new ItemValues*[ItemsCount];

	itemValues[Item::Material] = new ItemValues[MaterialsCount]
	{
		ItemValues(15, 1, 1, 1), // Scrap
		ItemValues(15, 1, 1, 1), // Cooper
		ItemValues(15, 1, 1, 1), // Iron
		ItemValues(15, 1, 1, 1), // Titan
		ItemValues(15, 1, 1, 1) // Diamond
	};

	itemValues[Item::Weapon] = new ItemValues[1]
	{
		ItemValues(15, 1, 1, 1)
	};

	itemValues[Item::Subsystem] = new ItemValues[SubsystemsCount]
	{
		ItemValues(15, 1, 1, 20),
		ItemValues(15, 1, 1, 20)
	};
}

void itemValuesDelete()
{
	for (int i = 0; i < ItemsCount; i++)
		delete[] itemValues[i];
	delete[] itemValues;
}

Item::Item(Position p, Item::Type type, int quantity)
	: DynamicObject(p, 0)
{
	m_item_type = type;
	m_quantity = quantity;
}

Item::Type Item::getItemType() const
{
	return m_item_type;
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