#ifndef END_SCENE_H
#define END_SCENE_H

#include"Scene.h"

class EndScene : public Scene
{
	Tab<GuiComponent*> *m_buttons;
	int m_btn_pressed;

public:
	EndScene(Game *g);
	~EndScene();
	void setActive();
	void setInactive();
	SceneType getNextScene();
	bool event(sf::Event &event, sf::Keyboard &keys, float time);
	bool update(sf::Event &event, sf::Keyboard &keys, float time);
	void draw(sf::RenderWindow &window);
};

#endif