#ifndef H_GAMEOBJECT
#define H_GAMEOBJECT

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

struct GameObject
{
	virtual void draw(sf::RenderWindow&) const;
	virtual sf::FloatRect getCollider() const;
	virtual void update(sf::Time const& dt) = 0; // pure virtual

protected:
	GameObject(std::string const&, sf::Vector2f const&);

	sf::Sprite sprite;
};

#endif H_GAMEOBJECT