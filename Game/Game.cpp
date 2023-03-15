#include"Game.h"

bool Game::slowDown = false;
bool Game::pause = false;
bool Game::mainShipControl = true;

Position Mouse::onScreenPos = Position();
Position Mouse::onWindowPos = Position();
IAction Mouse::leftButton = IAction::NONE;
IAction Mouse::rightButton = IAction::NONE;

Game::Game()
{
	loadDataFromFiles();
	init();
}

Game::~Game()
{
	deleteData();
	deleteDataFromFiles();
}

void Game::init()
{
	mainShipAlive = true;

	camera = new Camera({ (float)Camera::screenWidth / 2, (float)Camera::screenHeight / 2 }, -(float)Camera::screenWidth / 2, 0, 90);

	shapeTab = new Tab<Shape*>(4);
	shapeTab->setElement(new Rectangle(200, 200, 200, 100, 45), 0);
	shapeTab->setElement(new Circle(200.0f + 100.0f * sqrt(2), 200.0f + 100.0f * sqrt(2), 25), 1);
	shapeTab->setElement(new Circle(360, 640, 25), 2);
	shapeTab->setElement(new Circle(40, 100, 25), 3);

	shipTab = new Tab<Ship*>(3);
	shipTab->setElement(new Ship({ 0, 0 }, 0, ShipType::Ship2, textures), 0);
	shipTab->setElement(new Ship({ 500, 300 }, 0, ShipType::Ship1, textures), 1);
	shipTab->setElement(new Ship({ 500, 500 }, 0, ShipType::Ship3, textures), 2);
	mainShip = shipTab->getElement(0);

	droneTab = new Tab<Drone*>(4);
	droneTab->setElement(new AttackDrone({ 300, 400 }, 0, textures), 0);
	//((AttackDrone*)droneTab->getElement(0))->test();
	droneTab->setElement(new ShieldDrone({ 400, 100 }, 0, textures), 1);
	droneTab->setElement(new AttackDrone({ 500, 700 }, 0, textures), 2);
	droneTab->setElement(new AttackDrone({ 600, 500 }, 0, textures), 3);

	towerTab = new Tab<Tower*>(1);
	towerTab->setElement(new DefenceTower1({ 250, -150 }, 30, textures), 0);

	unitsGroupTab = new Tab<UnitsGroup*>(3);
	unitsGroupTab->setElement(new UnitsGroup(GroupType::REBEL, shipTab->getElement(0)), 0);
	unitsGroupTab->getElement(0)->addUnit(droneTab->getElement(0));
	unitsGroupTab->getElement(0)->addUnit(droneTab->getElement(1));
	unitsGroupTab->getElement(0)->addUnit(towerTab->getElement(0));

	unitsGroupTab->setElement(new UnitsGroup(GroupType::COLONIAL, shipTab->getElement(1)), 1);
	unitsGroupTab->getElement(1)->addUnit(droneTab->getElement(2));

	unitsGroupTab->setElement(new UnitsGroup(GroupType::COLONIAL, shipTab->getElement(2)), 2);
	unitsGroupTab->getElement(2)->addUnit(droneTab->getElement(3));

	if (true)
	{
		shipTab->getElement(1)->setTarget(mainShip);
		shipTab->getElement(2)->setTarget(mainShip);
	}

	ammoTab = new SnakeTab<Ammo*>();

	itemTab = new SnakeTab<Item*>();
	itemTab->add(new Material({ 600.f, 600.f }, MaterialType::Scrap));
	itemTab->add(new Material({ 700.f, 600.f }, MaterialType::Coopper));
	itemTab->add(new Material({ 600.f, 700.f }, MaterialType::Iron));
	itemTab->add(new Material({ 700.f, 700.f }, MaterialType::Titan));
	itemTab->add(new Subsystem({ 200.f, 100.f }, SubsystemType::Teleport));
	itemTab->add(new Subsystem({ 300.f, 100.f }, SubsystemType::SlowDown));
	itemTab->add(new Subsystem({ 350.f, 100.f }, SubsystemType::SlowDown));

	inventory = new Inventory();
}

void Game::deleteData()
{
	for (int i = 0; i < shapeTab->getSize(); i++)
		delete (*shapeTab)[i];
	delete shapeTab;

	for (int i = 0; i < unitsGroupTab->getSize(); i++)
		delete (*unitsGroupTab)[i];
	delete unitsGroupTab;

	for (int i = 0; i < shipTab->getSize(); i++)
		delete (*shipTab)[i];
	delete shipTab;

	for (int i = 0; i < droneTab->getSize(); i++)
		delete (*droneTab)[i];
	delete droneTab;

	for (int i = 0; i < towerTab->getSize(); i++)
		delete (*towerTab)[i];
	delete towerTab;

	delete camera;

	for (SnakeTabElement<Ammo*> *element = ammoTab->getFirst(); element != nullptr; element = element->getNext())
		delete element->getContent();
	delete ammoTab;

	for (SnakeTabElement<Item*> *element = itemTab->getFirst(); element != nullptr; element = element->getNext())
		delete element->getContent();
	delete itemTab;

	delete inventory;
}

void Game::loadDataFromFiles()
{
	background.loadFromFile(fileName("background2.jpg"));

	textures = new Tab<sf::Texture*>((int)Textures::SIZE);
	for (int i = 0; i < (int)Textures::SIZE; i++)
		textures->setElement(new sf::Texture(), i);

	sf::Image image;
	image.loadFromFile(fileName("statki5.png"));
	textures->getElement(0)->loadFromImage(image, sf::IntRect(0, 0, 40, 54));
	textures->getElement(1)->loadFromImage(image, sf::IntRect(40, 0, 50, 83));
	textures->getElement(2)->loadFromImage(image, sf::IntRect(140, 47, 60, 23));
	textures->getElement(3)->loadFromImage(image, sf::IntRect(0, 54, 20, 20));
	textures->getElement(4)->loadFromImage(image, sf::IntRect(0, 74, 26, 26));
	textures->getElement(5)->loadFromImage(image, sf::IntRect(120, 67, 20, 33));
	textures->getElement(6)->loadFromImage(image, sf::IntRect(172, 80, 28, 20));
}


void Game::deleteDataFromFiles()
{
	for (int i = 0; i < (int)Textures::SIZE; i++)
		delete (*textures)[i];
	delete textures;
}

void Game::deleteAmmoUnitsGroup(UnitsGroup *group)
{
	SnakeTabElement<Ammo*> *element = ammoTab->getFirst();
	SnakeTabElement<Ammo*> *next;

	while (element != nullptr)
	{
		next = element->getNext();

		Ammo *ammo = element->getContent();
		if (ammo->getGroup() == group)
			ammo->setGroup(nullptr);

		element = next;
	}
}

void Game::updateAmmo(float time)
{
	float newTime = (slowDown ? slowDownTime : 1) * time;
	SnakeTabElement<Ammo*> *element = ammoTab->getFirst();
	SnakeTabElement<Ammo*> *next;

	while (element != nullptr)
	{
		next = element->getNext();

		bool stillAlive = element->getContent()->move(newTime); // "still alive" XD
		if (!stillAlive)
		{
			delete element->getContent();
			ammoTab->remove(element);
			delete element;
		}

		element = next;
	}
}

void Game::updatePositions(sf::Event &event, sf::Keyboard &keys, float time)
{
	float newTime = (slowDown ? slowDownTime : 1 ) * time;

	mainShip->motionUpdate(keys, time);
	mainShip->shootUpdate(keys, newTime, ammoTab);
	for (size_t i = 1; i < shipTab->getSize(); i++)
	{
		(*shipTab)[i]->motionUpdate(newTime);
		(*shipTab)[i]->shootUpdate(newTime, ammoTab);
	}

	for (size_t i = 0; i < droneTab->getSize(); i++)
		droneTab->getElement(i)->update(newTime, ammoTab);
	
	for (size_t i = 0; i < towerTab->getSize(); i++)
		towerTab->getElement(i)->update(newTime, ammoTab);

	for (int i = 0; i < shapeTab->getSize(); i++)
	{
		Shape *shape = shapeTab->getElement(i);

		SnakeTabElement<Ammo*> *element = ammoTab->getFirst();
		SnakeTabElement<Ammo*> *next;

		while (element != nullptr)
		{
			next = element->getNext();

			bool stillAlive = shape->posIn(element->getContent()->getPosition()); // "still alive" XD (again)
			if (stillAlive)
			{
				delete element->getContent();
				ammoTab->remove(element);
				delete element;
			}

			element = next;
		}
	}
}

bool Game::updateShips(float time)
{
	float newTime = (slowDown ? slowDownTime : 1) * time;

	for (int i = 0; i < shipTab->getSize(); i++)
	{
		Ship *ship = shipTab->getElement(i);
		if (ship->isTouching(ammoTab, newTime))
		{
			// ship destroyed

			updateUnitsTargets(ship);

			updateUnitsGroup(ship);

			changeItems(ship);

			delete ship;
			shipTab->removeElement(i--);
			if (i == -1)
			{
				mainShipAlive = false;
				return false;
			}
		}
	}

	return true;
}

void Game::updateDrones(float time)
{
	float newTime = (slowDown ? slowDownTime : 1) * time;

	for (int i = 0; i < droneTab->getSize(); i++)
	{
		Drone *drone = (*droneTab)[i];
		if (drone->isTouching(ammoTab, newTime))
		{
			// drone destroyed

			updateUnitsTargets(drone);

			updateUnitsGroup(drone);

			changeItems(drone);

			delete drone;
			droneTab->removeElement(i--);
		}
	}
}

void Game::updateTowers(float time)
{
	float newTime = (slowDown ? slowDownTime : 1) * time;

	for (int i = 0; i < towerTab->getSize(); i++)
	{
		Tower *tower = (*towerTab)[i];
		if (tower->isTouching(ammoTab, newTime))
		{
			// tower destroyed

			updateUnitsTargets(tower);

			updateUnitsGroup(tower);

			changeItems(tower);

			delete tower;
			towerTab->removeElement(i--);
		}
	}
}

void Game::changeItems(Unit *unit)
{
	itemTab->add(new Material(unit->getPosition(), MaterialType::Diamond));
}

bool Game::pickUpItemTry(Position pos)
{
	float l = camera->getOnMapLength(1);
	//printf("l = %f\n", camera->getOnMapLength(1));
	for (SnakeTabElement<Item*> *elem = itemTab->getFirst(), *next = nullptr; elem != nullptr;)
	{
		next = elem->getNext();
		Item *item = elem->getContent();

		float dist = pos.distance(item->getPosition());
		if (dist < item->getPickUpRange() * l)
		{
			int ret = inventory->addItem(item);
			if (ret == 2)
			{
				itemTab->remove(elem);
				delete elem->getContent();
				delete elem;
				return true;
			}
			else if (ret == 1)
				return true;
		}

		elem = next;
	}
	return false;
}

void Game::updateUnitsGroup(Unit *unit)
{
	UnitsGroup *group = unit->getGroup();
	group->removeUnit(unit);

	if (group->getSize() == 0)
	{
		deleteAmmoUnitsGroup(group);

		size_t s = unitsGroupTab->getSize();
		for (int i = 0; i < s; i++)
		{
			if (unitsGroupTab->getElement(i) == group)
			{
				unitsGroupTab->removeElement(i);
				break;
			}
		}

		delete group;
	}
}

void Game::updateUnitsTargets(const Unit *unit)
{
	for (size_t i = 0; i < droneTab->getSize(); i++)
	{
		Drone *drone = droneTab->getElement(i);

		if (drone->getType() == DroneType::ATTACK1)
		{
			AttackDrone *atDrone = (AttackDrone*)drone;
			if (atDrone->getTarget() == unit)
				atDrone->setTarget(nullptr);
		}
	}

	for (size_t i = 0; i < shipTab->getSize(); i++)
	{
		Ship *shipPointer = shipTab->getElement(i);

		if (shipPointer->getTarget() == unit)
			shipPointer->setTarget(nullptr);
	}
	
	for (size_t i = 0; i < towerTab->getSize(); i++)
	{
		Tower *towerPointer = towerTab->getElement(i);

		if (towerPointer->getTarget() == unit)
			towerPointer->setTarget(nullptr);
	}
}

void Game::setMainTarget(Position mainPos)
{
	Unit *target;

	size_t si = 1, di = 0, ti = 0;

	if (shipTab->getSize() > si)
		target = shipTab->getElement(si++);
	else if (droneTab->getSize() > 0)
		target = droneTab->getElement(di++);
	else if (towerTab->getSize() > 0)
		target = towerTab->getElement(ti++);
	else
		target = nullptr;

	if (target != nullptr)
	{
		Position pos = target->getPosition();
		float dist = DISTANCE(pos.x, pos.y, mainPos.x, mainPos.y);
		Unit *element;

		while (si < shipTab->getSize())
		{
			element = shipTab->getElement(si);
			pos = element->getPosition();
			float d = DISTANCE(pos.x, pos.y, mainPos.x, mainPos.y);

			if (d < dist)
			{
				dist = d;
				target = element;
			}

			si++;
		}

		while (di < droneTab->getSize())
		{
			element = droneTab->getElement(di);
			pos = element->getPosition();
			float d = DISTANCE(pos.x, pos.y, mainPos.x, mainPos.y);

			if (d < dist)
			{
				dist = d;
				target = element;
			}

			di++;
		}

		while (ti < towerTab->getSize())
		{
			element = towerTab->getElement(ti);
			pos = element->getPosition();
			float d = DISTANCE(pos.x, pos.y, mainPos.x, mainPos.y);

			if (d < dist)
			{
				dist = d;
				target = element;
			}

			ti++;
		}

		//target->getPosition().print("\n");
	}

	mainShip->setTarget(target);
}

bool Game::isMainShipAlive()
{
	return mainShipAlive;
}

bool Game::event(sf::Event &event, sf::Keyboard &keys, float time)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			return false;
		case sf::Keyboard::Tab:
			//pause = !pause;
			break;
		case sf::Keyboard::Num1:
			if (inventory->contains(SubsystemType::SlowDown))
				slowDown = !slowDown;
			break;
		case sf::Keyboard::Num2:
		{
			if (!pause)
			{
				if (inventory->contains(SubsystemType::Teleport))
					mainShip->setPosition(camera->getPosFromScreen(Mouse::OnWindowPos()));
				//mouse.setPosition({1920 / 2, 1080 / 2});
			}
			break;
		}
		default:
			break;
		}
	}

	//if (!butt.getShape()->posIn(Mouse::OnWindowPos()))
	{
		if (Mouse::LButton() == IAction::PRESSED)
		{
			Position inGamePos = camera->getPosFromScreen(Mouse::OnWindowPos());
			bool setTarget = !pickUpItemTry(inGamePos);

			if (setTarget)
				setMainTarget(inGamePos);
		}
		else if (Mouse::RButton() == IAction::PRESSED)
			mainShip->setTarget(nullptr);
	}

	if (!pause)
		mainShip->event(event, keys, time);

	return true;
}

bool Game::update(sf::Event &event, sf::Keyboard &keys, float time)
{
	//for (int i = 0; i < shipTab->getSize(); i++)
	//	shipTab->getElement(i)->getGroup()->print("\n");
	//printf("\n");

	if (!pause)
	{
		//droneTab->getElement(0)->getGroup()->getMainUnit()->getPosition().print("\n");

		updateAmmo(time);

		updatePositions(event, keys, time);

		if (!updateShips(time))
			return false;
		updateDrones(time);
		updateTowers(time);
	}

	camera->update(keys, time, *mainShip);

	return true;
}

void Game::fromPauseMenuReturn()
{
	Position newPos = camera->getPosFromScreen(Mouse::OnWindowPos());
	camera->setPosition(mainShip->getPosition() + (newPos - camera->getPosition()));
}

void Game::draw(sf::RenderWindow &window) const
{
	//if (false)
	{
		float scale = 10, z = (float)Camera::screenWidth * scale + (float)Camera::screenWidth / 2;
		float sx = (float)background.getSize().x / (float)Camera::screenWidth;
		float sy = (float)background.getSize().y / (float)Camera::screenHeight;
		float w = z * sx * 2, h = z * sy * ((float)Camera::screenHeight / (float)Camera::screenWidth) * 2;
		Rectangle rect = Rectangle(-w / 2, -h / 2, w, h);
		Rectangle rect2 = camera->getOnScreenRect(rect, Camera::screenWidth * scale);

		sf::RectangleShape backgr;
		backgr.setTexture(&background);
		backgr.setSize({ rect2.w, rect2.h });
		backgr.setPosition(rect2.x, rect2.y);
		backgr.setRotation(rect2.rotation);
		window.draw(backgr);
	}

	for (SnakeTabElement<Ammo*> *element = ammoTab->getFirst(); element != nullptr; element = element->getNext())
		element->getContent()->draw(window, *camera);
	
	for (SnakeTabElement<Item*> *element = itemTab->getFirst(); element != nullptr; element = element->getNext())
		element->getContent()->draw(window, *camera);

	if (mainShip->getTarget() != nullptr)
		Circle(camera->getOnScreenPos(mainShip->getTarget()->getPosition()), 50 * camera->getScale()).draw(window, sf::Color(255, 0, 0, 63));

	for (int z = 0; z < 3; z++)
	{
		float funcZ = 100.0f - 100.0f * z;

		for (int i = 0; i < shapeTab->getSize(); i++)
		{
			Shape *shape = shapeTab->getElement(i);

			switch (shape->type)
			{
			case ShapeType::Rectangle:
				shape = &camera->getOnScreenRect(Rectangle(*(Rectangle*)shape), funcZ);
				break;
			case ShapeType::Circle:
				shape = &camera->getOnScreenCircle(Circle(*(Circle*)shape), funcZ);
				break;
			case ShapeType::Ellipse:
				shape = &camera->getOnScreenEllipse(Ellipse(*(Ellipse*)shape), funcZ);
				break;
			}
			shape->draw(window, sf::Color(0, 191 + 32 * z, 0, 255));
		}
	}

	for (int i = 0; i < shipTab->getSize(); i++)
		shipTab->getElement(i)->draw(window, *camera);

	for (int i = 0; i < droneTab->getSize(); i++)
		droneTab->getElement(i)->draw(window, *camera);
	
	for (int i = 0; i < towerTab->getSize(); i++)
		towerTab->getElement(i)->draw(window, *camera);

	Ship *ship = (*shipTab)[0];

	sf::RectangleShape rect;

	rect.setPosition(20, Camera::screenHeight - 90);
	rect.setSize({ ship->getEnergyAsF() * 400, 20 });
	rect.setFillColor(sf::Color::Green);
	window.draw(rect);

	rect.setPosition(20, Camera::screenHeight - 60);
	rect.setSize({ ship->getShieldAsF() * 400, 20 });
	rect.setFillColor(sf::Color::Blue);
	window.draw(rect);

	rect.setPosition(20, Camera::screenHeight - 30);
	rect.setSize({ ship->getArmorAsF() * 400, 20 });
	rect.setFillColor(sf::Color::Red);
	window.draw(rect);

	/*
	rect.setPosition(Camera::screenWidth / 4 - 1, 0);
	rect.setSize(sf::Vector2f(2, Camera::screenHeight));
	rect.setFillColor(sf::Color::Blue);
	window.draw(rect);
	*/

	Unit *target = mainShip->getTarget();
	if (target != nullptr)
	{
		if (target->getMaxShield() != 0)
		{
			float sh = target->getShieldAsF() * 400;

			rect.setPosition(Camera::screenWidth - sh - 20, Camera::screenHeight - 60);
			rect.setSize({ sh, 20 });
			rect.setFillColor(sf::Color::Blue);
			window.draw(rect);
		}

		float arm = target->getArmorAsF() * 400;
		
		rect.setPosition(Camera::screenWidth - arm - 20, Camera::screenHeight - 30);
		rect.setSize({ arm, 20 });
		rect.setFillColor(sf::Color::Red);
		window.draw(rect);
	}

	//printf("%f\n", camera->getOnMapLength(1, 0));
	//Pos pos1 = Pos(-camera->getOnMapLength(600, 0), 0);
	//Pos pos2 = Pos(camera->getOnMapLength(600, 0), 0);

	//camera->getOnScreenCircle(Circle(pos1, 10)).draw(window, sf::Color(0, 255, 255));
	//camera->getOnScreenCircle(Circle(pos2, 10)).draw(window, sf::Color(0, 255, 255));

	//butt.draw(window);

	//Circle(camera->getOnScreenPos(camera->getPosFromScreen(mousePosition)), 20).draw(window, sf::Color::Yellow);
}