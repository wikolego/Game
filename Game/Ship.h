#ifndef SHIP_H
#define SHIP_H

#include<string.h>

#include"Drones.h"
#include"Towers.h"

#define MAX_V 200.0f
#define MAX_VA 100.0f
//#define A_V 2.0f

#define MAX_RV 60.0f
#define MAX_RA 60.0f

enum class ShipType
{
	Ship1,
	Ship2,
	Ship3,
	NONE
};

class Ship : public Unit
{
	friend class Camera;
	//friend class Game;

	ShipType m_ship_type;

	Tab<Weapon*> *m_weapons;
	float m_energy;
	float m_max_energy;

	Unit *m_target;

	sf::Texture *m_texture;
	Position m_texture_position;
	
public:
	Ship();
	Ship(const Position &p, float rotation);
	Ship(const Position &p, float rotation, const ShipType &type, const Tab<sf::Texture*> *textures);
	~Ship();
	void setTarget(Unit *target);
	Unit *getTarget() const;
	float getEnergyAsF() const;
	void event(sf::Event &event, sf::Keyboard &keys, float time);
	void motionUpdate(float time);
	void motionUpdate(sf::Keyboard &keys, float time);
	void shootUpdate(float time, SnakeTab<Ammo*> *ammoTab);
	void shootUpdate(sf::Keyboard &keys, float time, SnakeTab<Ammo*> *ammoTab);
	void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif