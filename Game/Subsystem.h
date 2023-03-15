#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include"Item.h"

#define SubsystemsCount 2

enum class SubsystemType
{
	Teleport,
	SlowDown,
	NONE
};

class Subsystem : public Item
{
	SubsystemType m_subsystem_type;

public:
	Subsystem(Position p, SubsystemType type, int quantity = 1);
	SubsystemType getSubsystemType() const;
	void draw(sf::RenderWindow &window, const Camera &camera) const;
};

#endif