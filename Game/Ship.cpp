#include"Game.h"

Ship::Ship()
	: Unit()
{
	m_unit_type = UnitType::Ship;

	m_max_v = MAX_V;
	m_max_a = MAX_VA;
	m_max_rotation_v = MAX_RV;
	m_rotation_a = MAX_RA;

	setArmorAndShield(40, 60, 0, 10);

	m_weapons = new Tab<Weapon*>;
	m_weapons->addElement(new Laser1(), 0);

	if (m_texture->loadFromFile("C:\\Users\\PC\\Desktop\\Game files\\Statki3.png", sf::IntRect(0, 0, 40, 54)) == false)
		cout << "blad\n";

	m_texture_position = Position(-20, -27);

	m_shield = 60;

	setTarget(nullptr);

	printf("BUGBUG\n");
}

Ship::Ship(const Position &p, float rotation)
	: Unit({ p, rotation })
{
	m_unit_type = UnitType::Ship;

	m_max_v = MAX_V;
	m_max_a = MAX_VA;
	m_max_rotation_v = MAX_RV;
	m_rotation_a = MAX_RA;
	
	setArmorAndShield(40, 60, 0, 10);

	m_weapons = new Tab<Weapon*>();
	m_weapons->addElement(new Laser1(), 0);

	if (m_texture->loadFromFile("C:\\Users\\PC\\Desktop\\Game files\\Statki3.png", sf::IntRect(0, 0, 40, 54)) == false)
		cout << "blad\n";

	setTarget(nullptr);

	m_texture_position = Position(-20, -27);

	printf("BUGBUG\n");
}

Ship::Ship(const Position &p, float rotation, const ShipType &type, const Tab<sf::Texture*> *textures)
	: Unit({ p, rotation })
{
	m_unit_type = UnitType::Ship;

	m_max_v = MAX_V;
	m_max_a = MAX_VA;
	m_max_rotation_v = MAX_RV;
	m_rotation_a = MAX_RA;

	m_weapons = new Tab<Weapon*>;

	m_max_energy = 200;
	m_energy = m_max_energy;

	m_ship_type = type;

	switch (type)
	{
	case ShipType::Ship1:

		m_weapons->addElement(new Cannon1({ 27, 0 }));

		m_texture = textures->getElement((int)Textures::SHIP1);

		m_texture_position = Position(-20, -27);

		m_shapes.addElement(new Ellipse(0, 0, 54.0 / 1.5, 40.0 / 1.5));
		m_shapes.addElement(new Ellipse(0, 0, 27, 20));
		m_shapes.addElement(new Rectangle(-24, -18, 10, 48));

		setArmorAndShield(40, 30, 5, 5);

		break;
	case ShipType::Ship2:
		m_weapons->addElement(new Laser1({ 8, -20 }));
		m_weapons->addElement(new Laser1({ 8, 20 }));
		//m_weapons->addElement(new Laser1({ 16, -10 }));
		//m_weapons->addElement(new Laser1({ 16, 10 }));

		m_texture = textures->getElement((int)Textures::SHIP2);

		m_texture_position = Position(-25, -42);

		m_shapes.addElement(new Ellipse(0, 0, 84.0 / 1.5, 50.0 / 1.5));
		m_shapes.addElement(new Ellipse(0, 0, 42, 25));

		setArmorAndShield(200, 100, 20, 5);

		break;
	case ShipType::Ship3:
		m_weapons->addElement(new Laser2({ 6, 0 }));

		m_texture = textures->getElement((int)Textures::SHIP3);

		m_texture_position = Position(-30, -11.5);

		m_shapes.addElement(new Ellipse(0, 0, 23.0 / 1.5, 60.0 / 1.5));
		m_shapes.addElement(new Ellipse(-2.5, 0, 9, 29));
		m_shapes.addElement(new Ellipse(2, -23, 9.5, 7));
		m_shapes.addElement(new Ellipse(2, 23, 9.5, 7));

		setArmorAndShield(40, 30, 5, 5);

		break;
	default:
		break;
	}

	setTarget(nullptr);
}

Ship::~Ship()
{
	for (int i = 0; i < m_weapons->getSize(); i++)
		delete m_weapons->getElement(i);
	delete m_weapons;

	for (int i = 0; i < m_shapes.getSize(); i++)
		delete m_shapes.getElement(i);
}

void Ship::setTarget(Unit *target)
{
	m_target = target;
	
	if (m_group != nullptr)
	{
		if (m_group->getMainUnit() == this)
		{
			size_t size = m_group->getSize();

			for (size_t i = 0; i < size; i++)
			{
				Unit *u = m_group->getUnit(i);

				switch (u->getUnitType())
				{
				case UnitType::Drone:
				{
					Drone *drone = (Drone*)u;

					switch (drone->getType())
					{
					case DroneType::ATTACK1:
						((AttackDrone*)drone)->setTarget(target);
						break;
					case DroneType::ATTACK2:
						((AttackDrone2*)drone)->setTarget(target);
						break;
					}
					break;
				}
				case UnitType::Tower:
				{
					Tower *tower = (Tower*)u;
					tower->setTarget(target);
				}
				}
			}
		}
	}
}

Unit* Ship::getTarget() const
{
	return m_target;
}

float Ship::getEnergyAsF() const
{
	return m_energy / m_max_energy;
}

void Ship::event(sf::Event &event, sf::Keyboard &keys, float time)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Num1:
			
			break;
		case sf::Keyboard::Num2:

			break;
		case sf::Keyboard::Num3:

			break;
		}
	}
}

/*
void Ship::motionUpdate(float time)
{
	if (m_target != nullptr)
	{

		//m_rotation += MAX_RV * time;

		float toRotation = DIRECTION(m_position.x, m_position.y, m_target->getPosition().x, m_target->getPosition().y);
		float rotationDifference = m_rotation - toRotation;

		while (rotationDifference > 180)
			rotationDifference -= 360;
		while (rotationDifference < -180)
			rotationDifference += 360;

		//m_rotation += m_max_rotation_v * time;
		//fixRotation(m_rotation);

		///*
		//printf("%d\n", m_slowed);
		if (m_slowed >= 1)
			time /= 2.0f;

		if (rotationDifference < 0)
		{
			m_rotation += m_max_rotation_v * time;
		}
		else if (rotationDifference > 0)
		{
			m_rotation -= m_max_rotation_v * time;
		}
		//
	}

	m_energy = m_max_energy;

	//m_rotation = 0;
}
*/

void Ship::motionUpdate(float time)
{
	if (m_target != nullptr)
	{
		if (m_slowed >= 1)
			time /= 2.0f;

		float newRotationV = m_rotation_v;
		
		float toRotation = DIRECTION(m_position.x, m_position.y, m_target->getPosition().x, m_target->getPosition().y);
		float rotationDifference = m_rotation - toRotation;

		while (rotationDifference > 180)
			rotationDifference -= 360;
		while (rotationDifference < -180)
			rotationDifference += 360;

		if (rotationDifference < 0)
		{
			newRotationV += time * m_rotation_a;
			if (newRotationV > m_max_rotation_v)
				newRotationV = m_max_rotation_v;
		}
		else if (rotationDifference > 0)
		{
			newRotationV -= time * m_rotation_a;
			if (newRotationV < -m_max_rotation_v)
				newRotationV = -m_max_rotation_v;
		}

		float lastRotation = m_rotation;

		float averageRotationV = (m_rotation_v + newRotationV) / 2;

		m_rotation_v = newRotationV;

		m_rotation += averageRotationV * time;

		float averageRotation = (lastRotation + m_rotation) / 2;

		if (m_rotation < 0)
			m_rotation += 360;
		else if (m_rotation >= 360)
			m_rotation -= 360;

		float max_v_x = COS(averageRotation) * m_max_v;
		float max_v_y = SIN(averageRotation) * m_max_v;

		/*
		float slow = 1.0f + m_slowed * 0.25;
		max_v_x /= slow;
		max_v_y /= slow;
		*/

		float lastVX = m_v_x;
		float lastVY = m_v_y;

		float vxDifference = max_v_x - lastVX;
		float vyDifference = max_v_y - lastVY;

		float s = sqrt(vxDifference * vxDifference + vyDifference * vyDifference);

		m_a_x = vxDifference * m_max_a / s;
		m_a_y = vyDifference * m_max_a / s;

		if (m_v_x < max_v_x)
		{
			m_v_x += m_a_x * time;
			if (m_v_x > max_v_x)
				m_v_x = max_v_x;
		}
		else if (m_v_x > max_v_x)
		{
			m_v_x += m_a_x * time;
			if (m_v_x < max_v_x)
				m_v_x = max_v_x;
		}

		if (m_v_y < max_v_y)
		{
			m_v_y += m_a_y * time;
			if (m_v_y > max_v_y)
				m_v_y = max_v_y;
		}
		else if (m_v_y > max_v_y)
		{
			m_v_y += m_a_y * time;
			if (m_v_y < max_v_y)
				m_v_y = max_v_y;
		}

		float averageVX = (lastVX + m_v_x) / 2;
		float averageVY = (lastVY + m_v_y) / 2;

		m_position.x += averageVX * time;
		m_position.y += averageVY * time;
	}
	else
	{
		if (false)
		{
			float lastVX = m_v_x;
			m_v_x += m_max_a * time;
			if (m_v_x > m_max_v)
				m_v_x = m_max_v;
			m_position.x += (lastVX + m_v_x) / 2.0 * time;
		}
	}
}

void Ship::motionUpdate(sf::Keyboard &keys, float time)
{
	//printf("%d\n", m_slowed);

	//time /= (1.0f + m_slowed * 0.25);

	bool LShift = keys.isKeyPressed(sf::Keyboard::LShift);

	bool wKey = keys.isKeyPressed(sf::Keyboard::W);
	bool sKey = keys.isKeyPressed(sf::Keyboard::S);

	bool aKey = keys.isKeyPressed(sf::Keyboard::A);
	bool dKey = keys.isKeyPressed(sf::Keyboard::D);

	if (Game::mainShipControl == false)
	{
		LShift = false;
		wKey = false;
		sKey = false;
		aKey = false;
		dKey = false;
	}

	// rotation

	float newRotationV = m_rotation_v;
	float maxRotation = 0;

	if (aKey)
	{
		if (!dKey)
		{
			if (!sKey)
				maxRotation = -m_max_rotation_v;
			else
				maxRotation = m_max_rotation_v;
		}
	}
	else if (dKey)
	{
		if (!sKey)
			maxRotation = m_max_rotation_v;
		else
			maxRotation = -m_max_rotation_v;
	}

	if (newRotationV > maxRotation)
	{
		newRotationV -= time * m_rotation_a;
		if (newRotationV < maxRotation)
			newRotationV = maxRotation;
	}
	else if (newRotationV < maxRotation)
	{
		newRotationV += time * m_rotation_a;
		if (newRotationV > maxRotation)
			newRotationV = maxRotation;
	}

	float lastRotation = m_rotation;

	float averageRotationV = (m_rotation_v + newRotationV) / 2;

	m_rotation_v = newRotationV;

	m_rotation += averageRotationV * time;

	float averageRotation = (lastRotation + m_rotation) / 2;

	if (m_rotation < 0)
		m_rotation += 360;
	else if (m_rotation >= 360)
		m_rotation -= 360;

	// speed

	float max_v_x = 0;
	float max_v_y = 0;

	if (wKey)
	{
		if (!sKey)
		{
			max_v_x = COS(averageRotation) * m_max_v;
			max_v_y = SIN(averageRotation) * m_max_v;
		}
	}
	else if (sKey)
	{
		max_v_x = -COS(averageRotation) * m_max_v;
		max_v_y = -SIN(averageRotation) * m_max_v;
	}

	/*
	float slow = 1.0f + m_slowed * 0.25;
	max_v_x /= slow;
	max_v_y /= slow;
	*/

	float lastVX = m_v_x;
	float lastVY = m_v_y;

	if (!LShift)
	{
		float vxDifference = max_v_x - lastVX;
		float vyDifference = max_v_y - lastVY;

		float s = sqrt(vxDifference * vxDifference + vyDifference * vyDifference);

		m_a_x = vxDifference * m_max_a / s;
		m_a_y = vyDifference * m_max_a / s;
		
		// pierwszy sposob lepszy

		// 5.52
		// 5.50		
		
		//s = abs(vxDifference) + abs(vyDifference);

		//m_a_x = vxDifference * MAX_VA / s;
		//m_a_y = vyDifference * MAX_VA / s;
		
		// 5.52
		// 6.20

		if (m_v_x < max_v_x)
		{
			m_v_x += m_a_x * time;
			if (m_v_x > max_v_x)
				m_v_x = max_v_x;
		}
		else if (m_v_x > max_v_x)
		{
			m_v_x += m_a_x * time;
			if (m_v_x < max_v_x)
				m_v_x = max_v_x;
		}

		if (m_v_y < max_v_y)
		{
			m_v_y += m_a_y * time;
			if (m_v_y > max_v_y)
				m_v_y = max_v_y;
		}
		else if (m_v_y > max_v_y)
		{
			m_v_y += m_a_y * time;
			if (m_v_y < max_v_y)
				m_v_y = max_v_y;
		}
	}
	else // beta XD
	{
		m_v_x = COS(averageRotation) * m_max_v;
		m_v_y = SIN(averageRotation) * m_max_v;
	}

	float averageVX = (lastVX + m_v_x) / 2;
	float averageVY = (lastVY + m_v_y) / 2;

	m_position.x += averageVX * time;
	m_position.y += averageVY * time;

	if (m_v_x == 0 && m_v_y == 0)
		m_energy += 30 * time;
	else
		m_energy += 10 * time;

	if (m_energy > m_max_energy)
		m_energy = m_max_energy;
}

void Ship::shootUpdate(float time, SnakeTab<Ammo*> *ammoTab)
{
	size_t size = m_weapons->getSize();
	for (int i = 0; i < size; i++)
	{
		Weapon *weapon = m_weapons->getElement(i);

		weapon->updateTime(time);

		Ammo *ammo = weapon->shoot();
		if (ammo != nullptr)
		{
			ammo->setGroup(m_group);
			ammo->setPosition(getRelativePosition(weapon->getPosition()));
			ammo->setV(m_v_x, m_v_y, m_rotation + weapon->getRotation());
			ammoTab->add(ammo);
		}
	}
}

void Ship::shootUpdate(sf::Keyboard &keys, float time, SnakeTab<Ammo*> *ammoTab)
{
	bool Space = keys.isKeyPressed(sf::Keyboard::Space);

	if (Game::mainShipControl == false)
		Space = false;
	
	size_t size = m_weapons->getSize();
	for (int i = 0; i < size; i++)
	{
		Weapon *weapon = m_weapons->getElement(i);

		weapon->updateTime(time);

		if (Space)
		{
			float energy = weapon->getEnergy();
			if (energy <= m_energy)
			{
				Ammo *ammo = weapon->shoot();
				if (ammo != nullptr)
				{
					m_energy -= energy;
					ammo->setGroup(m_group);
					ammo->setPosition(getRelativePosition(weapon->getPosition()));
					ammo->setV(m_v_x, m_v_y, m_rotation + weapon->getRotation());
					ammoTab->add(ammo);
				}
			}
		}
		else
			weapon->notShoot(time);
	}
}

void Ship::draw(sf::RenderWindow &window, const Camera &camera) const
{
	Position draw_pos = m_position + m_texture_position;
	draw_pos.rotate(m_position, m_rotation + 90);

	Rectangle rect2 = camera.getOnScreenRect(Rectangle(draw_pos, Position(m_texture->getSize().x, m_texture->getSize().y), m_rotation + 90), 0);

	sf::RectangleShape rect;
	rect.setTexture(m_texture);
	rect.setSize({ rect2.w, rect2.h });
	rect.setPosition(rect2.x, rect2.y);
	rect.setRotation(rect2.rotation);
	window.draw(rect);

	Ellipse elp = *(Ellipse*)m_shapes.getElement(0);

	Position p = elp.getPosition();
	p.rotate(m_rotation);
	elp.setPosition(p + m_position);
	elp.rotate(m_rotation);

	camera.getOnScreenEllipse(elp, 0).draw(window, sf::Color((float)m_slowed / 4 * 255, 0, 255, getShieldAsF() * 127));

	window.draw(rect);
}

/*
void Ship::draw(sf::RenderWindow &window, const Camera &camera) const
{
	sf::RectangleShape rect;

	Position draw_pos = m_position + m_texture_position;
	draw_pos.rotate(m_position, m_rotation + 90);

	draw_pos = camera.getOnScreenPos(draw_pos);

	rect.setPosition(draw_pos.x, draw_pos.y);
	rect.setRotation(m_rotation + 90 - camera.getRectangle().rotation);

	float scale = camera.getScale();

	sf::Vector2u vec = m_texture->getSize();

	rect.setSize({ vec.x * scale, vec.y * scale });
	rect.setTexture(m_texture);

	Ellipse elp = *(Ellipse*)m_shapes.getElement(0);

	Position p = elp.getPosition();
	p.rotate(m_rotation);
	elp.setPosition(p + m_position);
	elp.rotate(m_rotation);

	camera.getOnScreenEllipse(elp).draw(window, sf::Color((float)m_slowed / 4 * 255, 0, 255, getShieldAsF() * 127));

	window.draw(rect);
}
*/

/*
void Ship::update(sf::Event &event, sf::Keyboard &keys, float time, const Position &mouse)
{
	// rotation

	float time = time.asSeconds();

	bool Space = keys.isKeyPressed(sf::Keyboard::Space);

	bool wKey = keys.isKeyPressed(sf::Keyboard::W);
	bool sKey = keys.isKeyPressed(sf::Keyboard::S);

	bool aKey = keys.isKeyPressed(sf::Keyboard::A);
	bool dKey = keys.isKeyPressed(sf::Keyboard::D);

	float newRotationV = m_rotation_v;

	if (aKey)
	{
		if (!dKey)
		{
			newRotationV -= time * MAX_RV;
			if (newRotationV < -MAX_RV)
				newRotationV = -MAX_RV;
		}
	}
	else if (dKey)
	{
		newRotationV += time * MAX_RV;
		if (newRotationV > MAX_RV)
			newRotationV = MAX_RV;
	}
	else
	{
		if (newRotationV > 0)
		{
			newRotationV -= time * MAX_RV;
			if (newRotationV < 0)
				newRotationV = 0;
		}
		else if (newRotationV < 0)
		{
			newRotationV += time * MAX_RV;
			if (newRotationV > 0)
				newRotationV = 0;
		}
	}

	float lastRotation = m_rotation;

	float averageRotationV = (m_rotation_v + newRotationV) / 2;

	m_rotation_v = newRotationV;

	m_rotation += averageRotationV * time;

	float averageRotation = (lastRotation + m_rotation) / 2;

	if (m_rotation < 0)
		m_rotation += 360;
	else if (m_rotation >= 360)
		m_rotation -= 360;

	// speed

	if (wKey)
	{
		if (!sKey)
		{
			max_v_x = COS(averageRotation) * MAX_V;
			max_v_y = SIN(averageRotation) * MAX_V;
		}
	}
	else if (sKey)
	{
		max_v_x = -COS(averageRotation) * MAX_V;
		max_v_y = -SIN(averageRotation) * MAX_V;
	}
	else
	{
		max_v_x = 0;
		max_v_y = 0;
	}

	float lastVX = m_v_x;
	float lastVY = m_v_y;

	if (!Space)
	{
		float vxDifference = max_v_x - lastVX;
		float vyDifference = max_v_y - lastVY;

		float s = abs(vxDifference) + abs(vyDifference);

		m_a_x = vxDifference * MAX_VA / s;
		m_a_y = vyDifference * MAX_VA / s;

		//float s = vxDifference / vyDifference;

		if (m_v_x < max_v_x)
		{
			m_v_x += m_a_x * time;
			if (m_v_x > max_v_x)
				m_v_x = max_v_x;
		}
		else if (m_v_x > max_v_x)
		{
			m_v_x += m_a_x * time;
			if (m_v_x < max_v_x)
				m_v_x = max_v_x;
		}

		if (m_v_y < max_v_y)
		{
			m_v_y += m_a_y * time;
			if (m_v_y > max_v_y)
				m_v_y = max_v_y;
		}
		else if (m_v_y > max_v_y)
		{
			m_v_y += m_a_y * time;
			if (m_v_y < max_v_y)
				m_v_y = max_v_y;
		}
	}
	else // beta XD
	{
		m_v_x = COS(averageRotation) * MAX_V;
		m_v_y = SIN(averageRotation) * MAX_V;
	}

	float averageVX = (lastVX + m_v_x) / 2;
	float averageVY = (lastVY + m_v_y) / 2;

	m_position.x += averageVX * time;
	m_position.y += averageVY * time;
}
*/