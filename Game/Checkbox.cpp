#include"Checkbox.h"

Checkbox::Checkbox()
	: GuiComponent()
{
	m_checked = false;
}

Checkbox::Checkbox(Shape *shape)
	: GuiComponent(shape)
{
	m_checked = false;
}

Checkbox::~Checkbox()
{
	//delete m_shape;
}

bool Checkbox::event(sf::Event &e)
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

	if (released)
		m_checked = !m_checked;

	return released;
}

void Checkbox::draw(sf::RenderWindow &window) const
{
	if (m_shape->type != ShapeType::Rectangle)
		return;

	m_shape->draw(window);
}