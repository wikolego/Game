#ifndef CANNON1_H
#define CANNON1_H

#include"Weapon.h"

class Cannon1 : public Weapon
{

public:
	Cannon1();
	Cannon1(float time);
	Cannon1(const Position &pos, float rotation = 0);
	void notShoot(float time);
	Ammo* shoot();
};

#endif