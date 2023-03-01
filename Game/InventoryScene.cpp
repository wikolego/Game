#include"InventoryScene.h"

InventoryScene::InventoryScene(Game *g)
	: Scene(g)
{
	m_type = SceneType::Inventory;

	float w = 300, h = 50, w_diff = 50, y = 50;
	float x = (Camera::screenWidth - (w * 3 + w_diff * 2)) / 2;
	
	m_buttons = new Tab<GuiComponent*>(3);
	for (int i = 0; i < 3; i++)
		m_buttons->setElement(new Button(new Rectangle(x + (w + w_diff) * i, y, w, h)), i);
}

InventoryScene::~InventoryScene()
{
	for (int i = 0; i < 3; i++)
		delete (*m_buttons)[i];
	delete m_buttons;

	printf("Inv des\n");
}

void InventoryScene::setActive()
{
	for (int i = 0; i < 3; i++)
		m_buttons->getElement(i)->reset();

	m_game->mainShipControl = false;
}

void InventoryScene::setInactive()
{
	;
}

SceneType InventoryScene::getNextScene()
{
	return SceneType::Game;
}

bool InventoryScene::event(sf::Event &event, sf::Keyboard &keys, float time)
{
	return false;
}

bool InventoryScene::update(sf::Event &event, sf::Keyboard &keys, float time)
{
	if (keys.isKeyPressed(sf::Keyboard::Escape))
		return true;

	m_game->update(event, keys, time);
	return !m_game->isMainShipAlive();
}

void InventoryScene::draw(sf::RenderWindow &window)
{
	m_game->draw(window);

	for (int i = 0; i < 3; i++)
		m_buttons->getElement(i)->draw(window);
}