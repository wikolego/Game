#include"Ship.h"
#include"Mouse.h"
//#include"Camera.h"

Camera::Camera()
{
	m_position = Position(screenWidth / 2, screenHeight / 2);
	m_z = 0;
	m_view_angle = 90;
	m_view_tan = TAN(m_view_angle / 2);

	m_rotation = 0;
	m_scale = 1;
}

Camera::Camera(const Position &pos, float z, float rotation, float view_angle, float scale)
{
	m_position = pos;
	m_z = z;
	m_view_angle = view_angle;
	m_view_tan = TAN(m_view_angle / 2);

	m_rotation = rotation;
	m_scale = scale;
}

Camera::~Camera()
{
	;
}

void Camera::setPosition(const Position &pos)
{
	m_position = pos;
}

void Camera::setRotation(float r)
{
	m_rotation = r;
	updateTrigFunc();
}

void Camera::update(sf::Keyboard &keys, float time, const Ship &ship)
{

	bool upKey = keys.isKeyPressed(sf::Keyboard::Up);
	bool downKey = keys.isKeyPressed(sf::Keyboard::Down);
	bool leftKey = keys.isKeyPressed(sf::Keyboard::Left);
	bool rightKey = keys.isKeyPressed(sf::Keyboard::Right);

	/*
	m_scale += ((int)upKey - (int)downKey) * time;

	if (m_scale < 0.25)
		m_scale = 0.25;
	else if (m_scale > 4)
		m_scale = 4;
	*/
	
	///*
	m_z += ((int)upKey - (int)downKey) * time * (float)screenWidth / 4.0f;

	if (m_z < -(float)screenWidth)
		m_z = -(float)screenWidth;
	else if (m_z > -(float)screenWidth / 4.0f)
		m_z = -(float)screenWidth / 4.0f;

	//printf("%f\n", m_z);
	//*/

	/*
	m_view_angle += ((int)rightKey - (int)leftKey) * time * 90.0f / 4.0f;

	if (m_view_angle < 1)
		m_view_angle = 1;
	else if (m_view_angle > 180)
		m_view_angle = 180;

	m_view_tan = TAN(m_view_angle / 2);
	*/

	rotate(((int)rightKey - (int)leftKey) * time * 45);

	//Position mousePos = Position(mouse.getPosition().x, mouse.getPosition().y) - Position(320, 180);

	//mousePos = Mouse::getOnWindowPos();

	if (ship.getTarget() == nullptr)
	{
		Position newPos = getPosFromScreen(Mouse::OnWindowPos());
		m_position = ship.getPosition() + (newPos - m_position);
	}
	else
	{
		Position newPos = getPosFromScreen(Mouse::OnWindowPos());
		m_position = ship.getPosition() + (newPos - m_position);

		//m_position = (ship.getPosition() + ship.getTarget()->getPosition()) / 2;
		//m_rotation = rotation_difference(ship.getRotation(), ship.getTarget()->getRotation());

		//m_position = ship.getTarget()->getPosition();
		//setRotation(ship.getPosition().direction(ship.getTarget()->getPosition()));
	}

	//m_position.rotate(ship.getPosition(), m_rotation);
}

void Camera::updateTrigFunc()
{
	//printf("cameraCos = %f\n", cameraCos);

	cameraCos = COS(m_rotation);
	cameraSin = SIN(m_rotation);

	//screenWidth = 1280;
	//screenHeight = 720;
}

void Camera::rotate(float rotationChange)
{
	m_rotation = fixRotation(m_rotation + rotationChange);

	updateTrigFunc();
}

float Camera::getScale() const
{
	return m_scale;
}

Position Camera::getPosition() const
{
	return m_position;
}

Rectangle Camera::getRectangle() const
{
	Rectangle rect(0, 0, screenWidth * m_scale, screenHeight * m_scale, m_rotation);
	
	Position p = Position(0, 0);
	p.rotate(Position(rect.w / 2, rect.h / 2), m_rotation);

	rect.setPosition(p);

	return rect;
}

float Camera::getOnMapLength(float l, float z) const
{
	return l * ((z - m_z) * m_view_tan / float(screenWidth / 2));
}

Position Camera::getOnScreenPos(Position pos, float z) const
{
	pos.rotate({ m_position.x, m_position.y }, cameraCos, -cameraSin);

	Position halfScreenPos = Position(screenWidth / 2, screenHeight / 2);

	Position newPos = (((pos - m_position) * m_scale * halfScreenPos.x) / ((z - m_z) * m_view_tan)) + halfScreenPos;

	//newPos.x = m_scale * halfScreenPos.x * newPos.x + halfScreenPos.x;
	//newPos.y = m_scale * halfScreenPos.x * newPos.y + halfScreenPos.y;

	return newPos;
}

Rectangle Camera::getOnScreenRect(Rectangle rect, float z) const
{
	Position p = getOnScreenPos(rect.getPosition(), z);

	float s = (m_scale * (float)screenWidth / 2.0f) / ((z - m_z) * m_view_tan);

	rect.setPosition(p);
	rect.rotation -= m_rotation;
	rect.w *= s;
	rect.h *= s;

	return rect;
}

Circle Camera::getOnScreenCircle(Circle circle, float z) const
{
	Position p = getOnScreenPos(circle.getPosition(), z);

	float s = (m_scale * (float)screenWidth / 2.0f) / ((z - m_z) * m_view_tan);

	circle.setPosition(p);
	circle.radius *= s;

	return circle;
}

Ellipse Camera::getOnScreenEllipse(Ellipse ellipse, float z) const
{
	Position p = getOnScreenPos(ellipse.getPosition(), z);

	float s = (m_scale * (float)screenWidth / 2.0f) / ((z - m_z) * m_view_tan);

	// p * scale + Pos = newP
	// p * scale = newP - Pos
	// p = (newP - Pos) / scale

	ellipse.setPosition(p);
	ellipse.rotation -= m_rotation;
	ellipse.w *= s;
	ellipse.h *= s;

	return ellipse;
}

Position Camera::getPosFromScreen(Position pos, float z) const
{
	Position halfScreenPos = Position(screenWidth / 2, screenHeight / 2);

	Position newPos = m_position + ((pos - halfScreenPos) * (z - m_z) * m_view_tan) / (m_scale * halfScreenPos.x);
	newPos.rotate(m_position, cameraCos, cameraSin);
	//pos = pos + m_position;

	return newPos;
}

/*

	pos.rotate({ m_position.x, m_position.y }, cameraCos, -cameraSin);

	Position halfScreenPos = Position(screenWidth / 2, screenHeight / 2);

	Position newPos = (((pos - m_position) * m_scale * halfScreenPos.x) / ((z - m_z) * m_view_tan)) + halfScreenPos;

	//newPos.x = m_scale * halfScreenPos.x * newPos.x + halfScreenPos.x;
	//newPos.y = m_scale * halfScreenPos.x * newPos.y + halfScreenPos.y;

	return newPos;



	newPos = (((pos - m_position) * m_scale * halfScreenPos.x) / ((z - m_z) * m_view_tan)) + halfScreenPos
	newPos - halfScreenPos = ((pos - m_position) * m_scale * halfScreenPos.x) / ((z - m_z) * m_view_tan)
	(newPos - halfScreenPos) * ((z - m_z) * m_view_tan) = (pos - m_position) * m_scale * halfScreenPos.x
	((newPos - halfScreenPos) * ((z - m_z) * m_view_tan)) / (m_scale * halfScreenPos.x) = pos - m_position
	m_position + ((newPos - halfScreenPos) * ((z - m_z) * m_view_tan)) / (m_scale * halfScreenPos.x) = pos

	pos = m_position + ((newPos - halfScreenPos) * (z - m_z) * m_view_tan) / (m_scale * halfScreenPos.x)
*/

// old functions (for tests)

/*
void Camera::update(sf::Event &event, sf::Keyboard &keys, float time, const Position &mouse)
{
	float seconds = time.asSeconds();

	bool eKey = keys.isKeyPressed(sf::Keyboard::E);
	bool rKey = keys.isKeyPressed(sf::Keyboard::R);
	bool tKey = keys.isKeyPressed(sf::Keyboard::T);

	if (tKey)
	{
		m_position = Position(screenWidth / 2, screenHeight / 2);
		m_rotation = 0;
		m_scale = 1;

		updateTrigFunc();
	}
	else
		rotate(-(int)eKey * seconds * 45 + (int)rKey * seconds * 45);

	//_______________________________________________________________

	bool upKey = keys.isKeyPressed(sf::Keyboard::Up);
	bool downKey = keys.isKeyPressed(sf::Keyboard::Down);
	bool leftKey = keys.isKeyPressed(sf::Keyboard::Left);
	bool rightKey = keys.isKeyPressed(sf::Keyboard::Right);

	m_position.x += cameraCos * (-(int)leftKey + (int)rightKey) * seconds * 100;
	m_position.y += cameraSin * (-(int)leftKey + (int)rightKey) * seconds * 100;

	m_position.x += -cameraSin * (-(int)upKey + (int)downKey) * seconds * 100;
	m_position.y += cameraCos * (-(int)upKey + (int)downKey) * seconds * 100;  // wazne!!!

	//m_position.x += COS(m_rotation + 90) * (-(int)upKey + (int)downKey) * seconds * 100;
	//m_position.y += SIN(m_rotation + 90) * (-(int)upKey + (int)downKey) * seconds * 100;

	//m_position.print("\n");
}


*/