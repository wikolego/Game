#include"Button.h"

Button::Button()
	: GuiComponent()
{

}

Button::Button(Shape *shape)
	: GuiComponent(shape)
{

}

Button::~Button()
{
	//delete m_shape;
}

void Button::draw(sf::RenderWindow &window) const
{
	if (m_shape->type != ShapeType::Rectangle)
		return;

	m_shape->draw(window);
}