#include"MenuScene.h"

MenuScene::MenuScene(Game *g)
	: Scene(g)
{
	m_type = SceneType::Menu;

	float w = 200, x = (Camera::screenWidth - w) / 2;
	float h = 100, h_diff = 25, y = (Camera::screenHeight - (3 * h + 2 * h_diff)) / 2;

	m_buttons = new Tab<GuiComponent*>(3);
	for (int i = 0; i < 3; i++)
		m_buttons->setElement(new Button(new Rectangle(x, y + (h + h_diff) * i, w, h)), i);
	btnPressed = 3;
	escPressed = false;
}

MenuScene::~MenuScene()
{
	for (int i = 0; i < 3; i++)
		delete (*m_buttons)[i];
	delete m_buttons;

	printf("Menu des\n");
}

void MenuScene::setActive()
{
	for (int i = 0; i < 3; i++)
		m_buttons->getElement(i)->reset();

	escPressed = false;
}

void MenuScene::setInactive()
{
	;
}

SceneType MenuScene::getNextScene()
{
	switch (btnPressed)
	{
	case 0:
		return SceneType::Game;
	case 1:
		return SceneType::Game;
	case 2:
		return SceneType::NONE;
	}

	if (escPressed == true)
		return SceneType::Game;

	return SceneType::NONE;
}

bool MenuScene::event(sf::Event &event, sf::Keyboard &keys, float time)
{
	int i = 0;
	for (; i < 3; i++)
	{
		if (m_buttons->getElement(i)->event(event))
			break;
	}

	switch (i)
	{
	case 0:
		btnPressed = 0;
		return true;
	case 1:
		btnPressed = 1;
		m_game->deleteData();
		m_game->init();
		return true;
	case 2:
		btnPressed = 2;
		return true;
	}
	
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			escPressed = true;
			return true;
		}
	}

	return false;
}

bool MenuScene::update(sf::Event &event, sf::Keyboard &keys, float time)
{
	return false;
}

void MenuScene::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
		m_buttons->getElement(i)->draw(window);
}