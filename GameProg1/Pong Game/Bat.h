#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bat
{
private:
	Vector2f m_Position;
	// A RectangleShape object
	RectangleShape m_Shape;
	float m_Speed = 1000.0f;
	bool m_MovingDown = false;
	bool m_MovingUp = false;
	bool m_MovingRight = false;
	bool m_MovingLeft = false;
	float m_LeftBound;
	float m_RightBound;
public:
	Bat(float startX, float startY, float leftBound, float rightBound);
	FloatRect getPosition();
	RectangleShape getShape();
	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();
	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();
	void update(Time dt);
};