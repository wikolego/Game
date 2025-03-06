#ifndef CHECKBOX_H
#define CHECKBOX_H

#include"GuiComponent.h"

class Checkbox : public GuiComponent
{
	bool m_checked;
public:
	Checkbox();
	Checkbox(Shape *shape);
	~Checkbox();
	void setChecked(bool checked);
	bool getChecked();
	bool event(sf::Event &e);
	void draw(sf::RenderWindow &window) const;
};

#endif