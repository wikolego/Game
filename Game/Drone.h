#ifndef DRONE_H
#define DRONE_H

#include"Weapons.h"

enum class DroneType
{
	SHIELD1,
	DEFENCE1,
	ATTACK1,
	ATTACK2,
	NONE
};

class Drone : public Unit
{
protected:
	DroneType m_type;

	sf::Texture *m_texture;
	Position m_texture_position;
public:
	Drone();
	Drone(const Position &pos, float rotation, DroneType type);
	Drone(const Position &pos, float rotation, DroneType type, const Tab<sf::Texture*> *textures);
	virtual ~Drone();
	DroneType getType() const;
	virtual void update(float time, SnakeTab<Ammo*> *ammoTab) = 0;
	virtual void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif