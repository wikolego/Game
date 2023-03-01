#include"GameScene.h"

GameScene::GameScene(Game *g)
	: Scene(g)
{
	m_type = SceneType::Game;

	tabPressed = false;
}

GameScene::~GameScene()
{

	printf("Game des\n");
}

void GameScene::setActive()
{
	m_game->mainShipControl = true;
	m_game->fromPauseMenuReturn();
}

void GameScene::setInactive()
{
	;
}

SceneType GameScene::getNextScene()
{
	if (!m_game->isMainShipAlive())
		return SceneType::End;
	else
	{
		if (tabPressed)
			return SceneType::Inventory;
		else
			return SceneType::Menu;
	}
}

bool GameScene::event(sf::Event &event, sf::Keyboard &keys, float time)
{
	tabPressed = false;
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Tab)
		{
			tabPressed = true;
			return true;
		}
	}
	return !m_game->event(event, keys, time);
}

bool GameScene::update(sf::Event &event, sf::Keyboard &keys, float time)
{
	return !m_game->update(event, keys, time);
}

void GameScene::draw(sf::RenderWindow &window)
{
	m_game->draw(window);
}