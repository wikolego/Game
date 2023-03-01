#ifndef LASER2_H
#define LASER2_H

#include"Weapon.h"

class Laser2 : public Weapon
{

public:
	Laser2();
	Laser2(float time);
	Laser2(const Position &pos, float rotation = 0);
	void notShoot(float time);
	Ammo* shoot();
};

#endif