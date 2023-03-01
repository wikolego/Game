#ifndef DEFENSETOWER1_H
#define DEFENSETOWER1_H

#include"Tower.h"

class DefenceTower1 : public Tower
{

public:
	//DefenceTower1();
	DefenceTower1(const Position &pos, float rotation, const Tab<sf::Texture*> *textures);
	void update(float time, SnakeTab<Ammo*> *ammoTab);
};


#endif