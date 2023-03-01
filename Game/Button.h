#ifndef BUTTON_H
#define BUTTON_H

#include"GuiComponent.h"

class Button : public GuiComponent
{

public:
	Button();
	Button(Shape *shape);
	~Button();
	//bool event(sf::Event &e);
	void draw(sf::RenderWindow &window) const;
};

#endif