#ifndef INVENTORY_SCENE_H
#define INVENTORY_SCENE_H

#include"Scene.h"

class InventoryScene : public Scene
{
	Tab<GuiComponent*> *m_buttons;
public:
	InventoryScene(Game *g);
	~InventoryScene();
	void setActive();
	void setInactive();
	SceneType getNextScene();
	bool event(sf::Event &event, sf::Keyboard &keys, float time);
	bool update(sf::Event &event, sf::Keyboard &keys, float time);
	void draw(sf::RenderWindow &window);
};

#endif