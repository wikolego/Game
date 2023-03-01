#ifndef TOWER_H
#define TOWER_H

#include"Weapons.h"

enum class TowerType
{
	DefenceTower1,
	Tower2,
	NONE
};

class Tower : public Unit
{
protected:
	TowerType m_tower_type;
	Weapon *m_weapon;

	Unit *m_target;

	sf::Texture *m_texture;
	Position m_texture_position;
public:
	Tower();
	Tower(const Position &p, float rotation);
	Tower(const Position &p, float rotation, const TowerType &type, const Tab<sf::Texture*> *textures);
	virtual ~Tower();
	void setTarget(Unit *target);
	Unit* getTarget() const;
	TowerType getType() const;
	virtual void update(float time, SnakeTab<Ammo*> *ammoTab) = 0;
	virtual void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif