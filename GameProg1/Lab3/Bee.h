#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Bee
{
private:
	// Center of the circle around which the bee will move
	float circleCenterX = 450.0f;
	float circleCenterY = 450.0f;
	float radius = 200.0f;

	// Set the initial angle
	float angle = 0.0f;

	bool m_MovingClockwise = true;
	bool m_MovingCounterClockwise = false;

public:
	Bee(Texture& textureBee);
	Sprite spriteBee;
	void moveClockwise();
	void moveCounterClockwise();
	void update(Time dt);
};