#ifndef ATTACKDRONE2_H
#define ATTACKDRONE2_H

#include"Drone.h"

class AttackDrone2 : public Drone
{
	Unit *m_target;
public:
	AttackDrone2();
	AttackDrone2(const Position &pos, float rotation, const Tab<sf::Texture*> *textures, Unit *target = nullptr);
	void setTarget(Unit *target);
	Unit* getTarget() const;
	void update(float time, SnakeTab<Ammo*> *ammoTab);
	//void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif