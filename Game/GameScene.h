#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include"Scene.h"

class GameScene : public Scene
{
	bool tabPressed;
public:
	GameScene(Game *g);
	~GameScene();
	void setActive();
	void setInactive();
	SceneType getNextScene();
	bool event(sf::Event &event, sf::Keyboard &keys, float time);
	bool update(sf::Event &event, sf::Keyboard &keys, float time);
	void draw(sf::RenderWindow &window);
};

#endif