#ifndef GAME_H
#define GAME_H

#include<ctime>

#include"GraphicalUserInterface.h"
//#include"Camera.h"
#include"Ship.h"
#include"Inventory.h"

#define slowDownTime 0.25

#define fileName(name) "C:\\Game files\\" name

class Game
{
public:
	static bool pause;
	static bool slowDown;
	static bool mainShipControl;

private:
	bool mainShipAlive;

	sf::Texture background;

	Tab<sf::Texture*> *textures;

	Tab<Shape*> *shapeTab;

	Camera *camera;

	Ship *mainShip;
	Tab<Ship*> *shipTab;

	Tab<Drone*> *droneTab;

	Tab<Tower*> *towerTab;

	Tab<UnitsGroup*> *unitsGroupTab;

	SnakeTab<Ammo*> *ammoTab;

	SnakeTab<Item*> *itemTab;

	Inventory *inventory;

private:
	void loadDataFromFiles();
	void deleteDataFromFiles();
	void deleteAmmoUnitsGroup(UnitsGroup *group);
	void updateAmmo(float time);
	void updatePositions(sf::Event &event, sf::Keyboard &keys, float time);
	bool updateShips(float time);
	void updateDrones(float time);
	void updateTowers(float time);
	void changeItems(Unit *unit);
	bool pickUpItemTry(Position pos); // true - picked up item
	void updateUnitsGroup(Unit *unit);
	void updateUnitsTargets(const Unit *unit);
	void setMainTarget(Position mainPos);

public:
	Game();
	~Game();
	void init();
	void deleteData();
	bool isMainShipAlive();
	bool event(sf::Event &event, sf::Keyboard &keys, float time); // true - continue
	bool update(sf::Event &event, sf::Keyboard &keys, float time); // true - continue
	void fromPauseMenuReturn();
	void draw(sf::RenderWindow &window) const;
};

#endif