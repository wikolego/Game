#include"AttackDrone.h"

AttackDrone::AttackDrone()
	: Drone({ 0, 0 }, 0, DroneType::ATTACK1)
{
	m_target = nullptr;
	
	m_weapon = new Laser2(0);
	m_weapon->setTimeToShoot(m_weapon->getTimeToShoot() * 5);
	m_weapon->setPosition({ 0, 0 });
}

AttackDrone::AttackDrone(const Position &pos, float rotation, const Tab<sf::Texture*> *textures, Unit *target)
	: Drone(pos, rotation, DroneType::ATTACK1, textures)
{
	m_target = target;

	m_weapon = new Laser2(0);
	m_weapon->setTimeToShoot(m_weapon->getTimeToShoot() * 5);
	m_weapon->setPosition({ 0, 0 });
}

AttackDrone::~AttackDrone()
{
	delete m_weapon;
	//printf("AttackDrone\n");
}

/*
bool AttackDrone::isTouching(SnakeTab<Ammo*> *ammoTab, float time)
{
	bool totally_hited = false;
	size_t i = 0;
	size_t size = 1;
	Shape *shape;

	if (m_shield <= 0)
	{
		i = 1;
		size = m_shapes.getSize();
	}

	for (; i < size; i++)
	{
		shape = m_shapes.getElement(i);
		switch (shape->type)
		{
		case ShapeType::Rectangle:
			shape = &Rectangle(*(Rectangle*)shape);
			break;
		case ShapeType::Circle:
			shape = &Circle(*(Circle*)shape);
			break;
		case ShapeType::Ellipse:
			shape = &Ellipse(*(Ellipse*)shape);
			break;
		}

		Position p = shape->getPosition();
		p.rotate(m_rotation);
		shape->setPosition(p + m_position);
		shape->rotate(m_rotation);

		//_______________________________________________________________________________________________________

		SnakeTabElement<Ammo*> *element = ammoTab->getFirst();
		SnakeTabElement<Ammo*> *next;

		while (element != nullptr)
		{
			next = element->getNext();

			Ammo *ammo = element->getContent();

			bool this_unit = false;
			for (size_t n = 0; n < ammo->m_units->getSize(); n++)
			{
				if (ammo->m_units->getElement(n) == this)
				{
					this_unit = true;
					break;
				}
			}

			if (!this_unit)
			{
				bool hited = shape->posIn(ammo->getPosition());
				if (hited)
				{
					totally_hited = true;
					updateByDmg(ammo->m_armor_damage, ammo->m_shield_damage);
					delete element->getContent();
					ammoTab->remove(element);
					delete element;
				}
			}

			element = next;
		}
	}
	if (!totally_hited)
		updateShield(time);

	//printf("%f, %f\n", m_armor, m_shield);

	if (m_armor <= 0)
	{
		m_target = nullptr;
		return true;
	}
	return false;
}
*/

void AttackDrone::setTarget(Unit *target)
{
	if (target != nullptr)
	{
		if (target == this)
			m_target = nullptr;
		else if (target->getGroup() != m_group)
			m_target = target;
	}
	else
		m_target = nullptr;
}

Unit* AttackDrone::getTarget() const
{
	return m_target;
}

void AttackDrone::update(float time, SnakeTab<Ammo*> *ammoTab)
{
	if (m_group != nullptr)
	{
		if (m_group->getMainUnit() != nullptr)
		{
			Unit *to_unit = m_group->getMainUnit();

			Position p(0, 40);
			p.rotate(to_unit->getRotation());
			m_position = to_unit->getPosition() + p;
			m_v_x = to_unit->getVX();
			m_v_y = to_unit->getVY();

			if (m_target != nullptr)
			{
				Position pos = m_target->getPosition();
				m_rotation = DIRECTION(m_position.x, m_position.y, pos.x, pos.y);

				m_weapon->updateTime(time);
				Ammo *ammo = m_weapon->shoot();
				if (ammo != nullptr)
				{
					m_rotation = getR(*m_target, ammo->getMV());

					//Tab<Unit*> *tab = new Tab<Unit*>;
					//tab->init(2);
					//tab->setElement(this, 0);
					//tab->setElement(to_unit, 1);
					ammo->setGroup(m_group);
					ammo->setPosition(getRelativePosition(m_weapon->getPosition()));
					ammo->setV(m_v_x, m_v_y, m_rotation);
					ammoTab->add(ammo);
				}

				//m_target->setPosition(pos + Position(time * 10 * (rand() % 7 - 3), time * 10 * (rand() % 7 - 3)));
			}
			else
			{
				m_weapon->reset();
				m_rotation = to_unit->getRotation();
			}
		}
		else
		{
			m_v_x = 0;
			m_v_y = 0;
			setTarget(nullptr);
		}
	}
	else
	{
		m_v_x = 0;
		m_v_y = 0;
		setTarget(nullptr);
	}
}

void AttackDrone::test() const
{
	printf("%c\n", m_target != nullptr ? 'T' : 'F');
}

/*
void AttackDrone::draw(sf::RenderWindow &window, const Camera &camera) const
{
	sf::RectangleShape rect;

	Position draw_pos = m_position + m_texture_position;
	draw_pos.rotate(m_position, m_rotation);

	draw_pos = camera.getOnScreenPos(draw_pos);

	rect.setPosition(draw_pos.x, draw_pos.y);
	rect.setRotation(m_rotation - camera.getRectangle().rotation);

	float scale = camera.getScale();

	sf::Vector2u vec = m_texture->getSize();

	rect.setSize({ vec.x * scale, vec.y * scale });
	rect.setTexture(m_texture);

	window.draw(rect);
}
*/