#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include"Scene.h"

class MenuScene : public Scene
{
	Tab<GuiComponent*> *m_buttons;
	int btnPressed;
	bool escPressed;

public:
	MenuScene(Game *g);
	~MenuScene();
	void setActive();
	void setInactive();
	SceneType getNextScene();
	bool event(sf::Event &event, sf::Keyboard &keys, float time);
	bool update(sf::Event &event, sf::Keyboard &keys, float time);
	void draw(sf::RenderWindow &window);
};

#endif