#include "Bee.h"
// This is the constructor function
Bee::Bee(Texture& textureBee)
{
	spriteBee.setTexture(textureBee);

	// Set bee position to the center of the circle
	spriteBee.setPosition(circleCenterX, circleCenterY);
}

void Bee::moveClockwise()
{
	m_MovingClockwise = true;
	m_MovingCounterClockwise = false;
}
void Bee::moveCounterClockwise()
{
	m_MovingCounterClockwise = true;
	m_MovingClockwise = false;
}

void Bee::update(Time dt)
{
	float beeX;
	float beeY;
	if (m_MovingClockwise) {
		// Move the bee in a clockwise direction
		beeX = circleCenterX + radius * std::cos(angle);
		beeY = circleCenterY + radius * std::sin(angle);
		angle += 0.01f;
	}
	if (m_MovingCounterClockwise) {
		// Move the bee in a counter-clockwise direction, set the angle to negative
		beeX = circleCenterX + radius * std::cos(angle);
		beeY = circleCenterY + radius * std::sin(angle);
		angle -= 0.01f;
	}
	spriteBee.setPosition(beeX, beeY);
}