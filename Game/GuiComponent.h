#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include"Shapes.h"
#include"Mouse.h"

class GuiComponent
{
protected:
	Shape *m_shape;
	bool m_pressed;

public:
	GuiComponent();
	GuiComponent(Shape *shape);
	virtual ~GuiComponent();
	Shape* getShape() const;
	virtual void reset();
	virtual bool event(sf::Event &e);
	virtual void draw(sf::RenderWindow &window) const = 0;
};

#endif