#include"GuiComponent.h"

GuiComponent::GuiComponent()
{
	m_shape = nullptr;
	m_pressed = false;
}

GuiComponent::GuiComponent(Shape *shape)
{
	m_shape = shape;
	m_pressed = false;
}

GuiComponent::~GuiComponent()
{
	delete m_shape;
}

Shape* GuiComponent::getShape() const
{
	return m_shape;
}

void GuiComponent::reset()
{
	m_pressed = false;
}

bool GuiComponent::event(sf::Event &e)
{
	Pos mouse_p = Mouse::OnWindowPos();
	bool mouse_in_butt = m_shape->posIn(mouse_p);

	IAction left = Mouse::LButton();

	bool released = false;
	if (left == IAction::PRESSED)
	{
		if (mouse_in_butt)
			m_pressed = true;
		else
			m_pressed = false;
	}
	//else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	else if (left == IAction::RELEASED)
	{
		if (mouse_in_butt && m_pressed)
			released = true;
		m_pressed = false;
	}
	return released;
}