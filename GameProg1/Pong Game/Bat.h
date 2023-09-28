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
public:
	Bat(float startX, float startY);
	FloatRect getPosition();
	RectangleShape getShape();
	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();
	void update(Time dt);
};