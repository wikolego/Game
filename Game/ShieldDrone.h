#ifndef SHIELDDRONE_H
#define SHIELDDRONE_H

#include"Drone.h"

class ShieldDrone : public Drone
{

public:
	ShieldDrone();
	ShieldDrone(const Position &pos, float rotation, const Tab<sf::Texture*> *textures);
	void update(float time, SnakeTab<Ammo*> *ammoTab);
	//void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif