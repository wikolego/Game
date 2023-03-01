#ifndef ATTACKDRONE_H
#define ATTACKDRONE_H

#include"Drone.h"

class AttackDrone : public Drone
{
	Unit *m_target;
	Weapon *m_weapon;
public:
	AttackDrone();
	AttackDrone(const Position &pos, float rotation, const Tab<sf::Texture*> *textures, Unit *target = nullptr);
	~AttackDrone();
	void setTarget(Unit *target);
	Unit* getTarget() const;
	void update(float time, SnakeTab<Ammo*> *ammoTab);
	void test() const;
	//void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif