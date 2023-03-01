#ifndef AMMO_H
#define AMMO_H

//#include<SFML\Graphics.hpp>
#include"Camera.h"
#include"UnitsGroup.h"

enum class AmmoType
{
	Laser,
	Rocket
};

class Ammo : public DynamicObject
{
protected:
	friend class Unit;
	//friend class Ship;
	//friend class Drone;
	friend class AttackDrone;
	friend class AttackDrone2;

	UnitsGroup *m_group;

	AmmoType m_ammo_type;

	float m_shield_damage;
	float m_armor_damage;

	float m_time;
public:
	Ammo();
	Ammo(const AmmoType &at);
	Ammo(const AmmoType &at, const Position &p, float rotation, float vx, float vy, UnitsGroup *group);
	Ammo(const Ammo &a);
	~Ammo();
	//void operator=(const Ammo &a);
	void setGroup(UnitsGroup *group);
	void setV(float vx, float vy);
	void setV(float vx, float vy, float rotation);
	bool move(float time); // returns true, when it can still move
	UnitsGroup* getGroup() const;
	void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif