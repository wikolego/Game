#ifndef MOUSE_H
#define MOUSE_H

#include"Position.h"
#include<SFML\Graphics.hpp>

enum class InputAction
{
	NONE, // 00
	PRESSED, // 01
	RELEASED, // 10
	ACTIVE // 11
};

typedef InputAction IAction;

class Mouse
{

	static Position onScreenPos;
	static Position onWindowPos;
	static IAction leftButton;
	static IAction rightButton;

	static void fixPressed(sf::Mouse &mouse)
	{
		int lastPressed = ((int)leftButton & (int)IAction::PRESSED) << 1;
		int nowPressed = (int)mouse.isButtonPressed(sf::Mouse::Left);
		leftButton = IAction(lastPressed | nowPressed);

		lastPressed = ((int)rightButton & (int)IAction::PRESSED) << 1;
		nowPressed = (int)mouse.isButtonPressed(sf::Mouse::Right);
		rightButton = IAction(lastPressed | nowPressed);
	}
public:
	static void update(sf::RenderWindow &window, sf::Event &event, sf::Mouse &mouse)
	{
		if (event.type == sf::Event::MouseMoved)
		{
			onWindowPos = Position((float)event.mouseMove.x, (float)event.mouseMove.y);
		}
		//int lastly = ((int)leftButton << 2) | (int)rightButton;
		fixPressed(mouse);
		//int now = ((int)leftButton << 2) | (int)rightButton;
		//if (lastly != now)
		//	printf("left - %d, right - %d\n", (int)leftButton, (int)rightButton);
	};
	static Position OnWindowPos()
	{
		return onWindowPos;
	}
	static IAction LButton()
	{
		return leftButton;
	}
	static IAction RButton()
	{
		return rightButton;
	}
};

#endif