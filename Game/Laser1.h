#ifndef LASER1_H
#define LASER1_H

#include"Weapon.h"

class Laser1 : public Weapon
{

public:
	Laser1();
	Laser1(float time);
	Laser1(const Position &pos, float rotation = 0);
	void notShoot(float time);
	Ammo* shoot();
};

#endif