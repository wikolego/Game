#include"SceneManager.h"

SceneManager::SceneManager(Game *g, SceneType active)
{
	m_game = g;
	
	m_scenes[0] = new GameScene(g);
	m_scenes[1] = new InventoryScene(g);
	m_scenes[2] = new MenuScene(g);
	m_scenes[3] = new EndScene(g);

	m_act_sc_type = active;
	m_active_scene = m_scenes[(int)m_act_sc_type];
	m_active_scene->setActive();
}

SceneManager::~SceneManager()
{
	printf("ScnManager des beg\n\n");

	for (int i = 0; i < ScenesCount; i++)
		delete m_scenes[i];

	printf("\nScnManager des end\n");
}

Scene* SceneManager::getActiveScene() const
{
	return m_active_scene;
}

SceneType SceneManager::getActiveSceneType() const
{
	return m_act_sc_type;
}

void SceneManager::changeScene()
{
	m_act_sc_type = m_active_scene->getNextScene();

	m_active_scene->setInactive();

	//printf("From %d ", (int)m_active_scene->getType());

	if (m_act_sc_type == SceneType::NONE)
		return;

	m_active_scene = m_scenes[(int)m_act_sc_type];
	m_active_scene->setActive();

	//printf("to %d\n", (int)m_active_scene->getType());
}