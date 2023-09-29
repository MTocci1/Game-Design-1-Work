#include "Ball.h"
// This is the constructor function
Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
	m_Shape.setSize(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Position);
}

FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}
RectangleShape Ball::getShape()
{
	return m_Shape;
}
float Ball::getXVelocity()
{
	return m_DirectionX;
}
void Ball::reboundSides()
{
	m_DirectionY = -m_DirectionY;
}
void Ball::reboundBatOrTop()
{
	m_DirectionX = -m_DirectionX;
}
void Ball::reboundBottom()
{
	m_Position.y = 500;
	m_Position.x = 1900;
	m_DirectionX = -m_DirectionX;
}

// Increase speed when ball hits bat
void Ball::hitBat()
{
	m_Speed += 500.0;
}
void Ball::resetSpeed()
{
	m_Speed = 900.0;
}

void Ball::slow()
{
	m_Speed -= 500.0;
	isDragActive = false;
}
void Ball::endSlow()
{
	m_Speed += 500.0;
	isDragActive = true;
}

void Ball::update(Time dt)
{
	// Update the ball's position
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x -= m_DirectionX * m_Speed * dt.asSeconds();

	// Apply drag to the ball so it slows down overtime
	if (isDragActive) {
		m_Speed -= m_Drag * dt.asSeconds();
	}

	// Ensure the ball doesn't change direction due to drag
	if (m_Speed <= 50.0)
	{
		m_Speed = 50.0;
	}

	// Ensure the ball doesn't change direction due to drag
	if (m_Speed >= 5000.0)
	{
		m_Speed = 5000.0;
	}

	// Move the ball 
	m_Shape.setPosition(m_Position);
}