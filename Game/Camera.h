#ifndef CAMERA_H
#define CAMERA_H

#include"Shapes.h"

class Ship;

class Camera
{
	Position m_position;
	float m_z;
	float m_view_angle;
	float m_view_tan;

	float m_rotation;
	float m_scale;
public:
	static float cameraCos;
	static float cameraSin;

	static unsigned int screenWidth;
	static unsigned int screenHeight;

	Camera();
	Camera(const Position &pos, float z, float rotation, float view_angle, float scale = 1);
	~Camera();
	void setPosition(const Position &pos);
	void setRotation(float r);
	void update(sf::Keyboard &keys, float time, const Ship &ship);
	void updateTrigFunc();
	void rotate(float rotationChange);
	float getScale() const;
	Position getPosition() const;
	Rectangle getRectangle() const;
	float getOnMapLength(float l, float z = 0) const;
	Position getOnScreenPos(Position pos, float z = 0) const;
	Rectangle getOnScreenRect(Rectangle rect, float z = 0) const;
	Circle getOnScreenCircle(Circle circle, float z = 0) const;
	Ellipse getOnScreenEllipse(Ellipse ellipse, float z = 0) const;
	Position getPosFromScreen(Position pos, float z = 0) const;
};

#endif