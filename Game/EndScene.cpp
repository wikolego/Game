#include"EndScene.h"

EndScene::EndScene(Game *g)
	: Scene(g)
{
	m_type = SceneType::End;

	float w = 200, x = (Camera::screenWidth - w) / 2;
	float h = 100, h_diff = 25, y = (Camera::screenHeight - (2 * h + 1 * h_diff)) / 2;

	m_buttons = new Tab<GuiComponent*>(2);
	for (int i = 0; i < 2; i++)
		m_buttons->setElement(new Button(new Rectangle(x, y + (h + h_diff) * i, w, h)), i);
	m_btn_pressed = 2;
}

EndScene::~EndScene()
{
	for (int i = 0; i < 2; i++)
		delete (*m_buttons)[i];
	delete m_buttons;

	printf("End des\n");
}

void EndScene::setActive()
{
	for (int i = 0; i < 2; i++)
		m_buttons->getElement(i)->reset();
}

void EndScene::setInactive()
{

}

SceneType EndScene::getNextScene()
{
	if (m_btn_pressed == 0)
		return SceneType::Game;
	return SceneType::NONE;
}

bool EndScene::event(sf::Event &event, sf::Keyboard &keys, float time)
{
	int i = 0;
	for (; i < 2; i++)
	{
		if (m_buttons->getElement(i)->event(event))
			break;
	}

	if (i == 2)
		return false;

	m_btn_pressed = i;
	if (m_btn_pressed == 0)
	{
		m_game->deleteData();
		m_game->init();
	}
	
	return true;
}

bool EndScene::update(sf::Event &event, sf::Keyboard &keys, float time)
{
	return false;
}

void EndScene::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 2; i++)
		m_buttons->getElement(i)->draw(window);
}