#ifndef SCENE_H
#define SCENE_H

#include"Game.h"

enum class SceneType
{
	Game,
	Inventory,
	Menu,
	End,
	NONE
};

#define ScenesCount 4

class Scene
{
protected:
	friend class SceneManager;

	SceneType m_type;

	Game *m_game;

public:
	Scene(Game *g)
	{
		m_game = g;
		m_type = SceneType::NONE;
	}
	virtual ~Scene()
	{
		printf("(sc des)\n");
	}
	virtual void setActive() = 0;
	virtual void setInactive() = 0;
	SceneType getType()
	{
		return m_type;
	}
	virtual SceneType getNextScene() = 0;
	virtual bool event(sf::Event &event, sf::Keyboard &keys, float time) = 0;
	virtual bool update(sf::Event &event, sf::Keyboard &keys, float time) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	//virtual void del() = 0; // delete
};

#endif