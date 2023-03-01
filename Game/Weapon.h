#ifndef WEAPON_H
#define WEAPON_H

#include"Ammo.h"

enum class WeaponType {
	Laser1,
	Laser2,
	Cannon1
};

class Weapon
{
protected:
	WeaponType m_weapon_type;

	float m_time;

	float m_time_to_shoot;

	bool m_ready_to_shoot;

	float m_shield_damage;
	float m_armor_damage;

	float m_accuracy; // accuracy in degrees: 0 - best accuracy

	float m_energy;

	float m_rotation;

	Position m_position;

	sf::RectangleShape *m_shape;
public:
	Weapon();
	Weapon(WeaponType wt);
	Weapon(const Weapon &wp);
	Weapon(const Position &pos, float rotation, WeaponType wt);
	void operator=(const Weapon &wp);
	void setPosition(const Position &p);
	void setRotation(float rotation);
	void setTimeToShoot(float time);
	void setTime(float time);
	void setTexture(sf::Texture *texture, const sf::IntRect &rect);
	Position getPosition() const;
	float getRotation() const;
	float getEnergy() const;
	float getAccuracy() const;
	float getTimeToShoot() const;
	float getTime() const;
	sf::RectangleShape* getShape() const;
	virtual void reset();
	virtual void updateTime(float time);
	virtual void notShoot(float time);
	virtual Ammo* shoot() = 0;
	virtual void draw(sf::RenderWindow &window, const Camera &camera);
	virtual void draw(sf::RenderWindow &window);
};

#endif