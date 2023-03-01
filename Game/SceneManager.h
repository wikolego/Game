#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include"GameScene.h"
#include"InventoryScene.h"
#include"MenuScene.h"
#include"EndScene.h"

class SceneManager
{
	Game *m_game;

	Scene *m_scenes[ScenesCount];

	Scene *m_active_scene;
	SceneType m_act_sc_type;

public:
	SceneManager(Game *g, SceneType active);
	~SceneManager();
	Scene* getActiveScene() const;
	SceneType getActiveSceneType() const;
	void changeScene();
};

#endif