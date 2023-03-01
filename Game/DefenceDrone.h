#ifndef DEFENCEDRONE_H
#define DEFENCEDRONE_H

#include"Drone.h"

class DefenceDrone : public Drone
{
	Weapon *m_weapon;
public:
	DefenceDrone();
	DefenceDrone(const Position &pos, float rotation, const Tab<sf::Texture*> *textures);
	void update(float time, SnakeTab<Ammo*> *ammoTab);
	//void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif