#include "Bee.h"

using namespace sf;
using namespace std;

Bee::Bee(sf::Vector2f const& position) 
	: GameObject("graphics/bee.png", position), velocity(0, 0)
{}

void Bee::update(sf::Time const& dt)
{
	prevPosition = sprite.getPosition();
	Vector2f newPosition = prevPosition + dt.asSeconds() * speed * velocity;
	sprite.setPosition(newPosition);

}

void Bee::handleInput(sf::Event const& event)
{
	if (event.type == Event::KeyPressed) {
		handleKeyEvent(event.key, true);
	} 
	else if (event.type == Event::KeyReleased) {
		handleKeyEvent(event.key, false);
	}
}


void Bee::handleKeyEvent(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code) {
	case Keyboard::W:
		isPressed ? moveUp() : stopUp();
		break;
	case Keyboard::A:
		isPressed ? moveLeft() : stopLeft();
		break;
	case Keyboard::S:
		isPressed ? moveDown() : stopDown();
		break;
	case Keyboard::D:
		isPressed ? moveRight() : stopRight();
		break;
	}
}

void Bee::cancelMove() {
	sprite.setPosition(prevPosition);
}

void Bee::moveLeft()
{
	velocity.x = -1;
}

void Bee::moveRight()
{
	velocity.x = +1;
}

void Bee::moveUp()
{
	velocity.y = -1;
}

void Bee::moveDown()
{
	velocity.y = +1;
}

void Bee::stopLeft()
{
	velocity.x = std::max(0.0f, velocity.x);
}

void Bee::stopRight()
{
	velocity.x = std::min(0.0f, velocity.x);
}

void Bee::stopUp()
{
	velocity.y = std::max(0.0f, velocity.y);
}

void Bee::stopDown()
{
	velocity.y = std::min(0.0f, velocity.y);
}