#ifndef H_BEE
#define H_BEE

#include "gameObject.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Bee : public GameObject
{
public:
	Bee(sf::Vector2f const&);

	void handleInput(sf::Event const&);
	void update(sf::Time const&); // override the base class method
	void cancelMove();

private:
	float speed = 300.0f;
	sf::Vector2f velocity;
	sf::Vector2f prevPosition;

	void handleKeyEvent(sf::Event::KeyEvent key, bool isPressed);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
};

#endif H_BEE