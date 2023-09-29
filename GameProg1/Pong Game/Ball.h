#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Ball
{
private:
	Vector2f m_Position;
	RectangleShape m_Shape;
	float m_Speed = 900.0f;

	// Add Drag
	float m_Drag = 20.f;
	bool isDragActive = true;

	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

	// Slow ball ability
	bool isSlowActive = false;

	bool hasHitBat = false;

public:
	Ball(float startX, float startY, Texture& textureBall);
	FloatRect getPosition();
	RectangleShape getShape();
	Sprite spriteBall;
	float getXVelocity();
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();
	void hitBat();
	void resetSpeed();
	void slow();
	void endSlow();
	void update(Time dt);
};