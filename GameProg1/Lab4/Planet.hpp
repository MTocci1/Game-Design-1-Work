#ifndef HPP_PLANET
#define HPP_PLANET

#include <SFML/Graphics.hpp>
#include "Subject.hpp"
#include "Event.hpp"

class Planet : public Subject {
public:
    Planet(sf::Texture const&, sf::Vector2f const&);
    void draw(sf::RenderWindow&) const;
    sf::FloatRect const& getCollider() const;
    void hit();
private:
    sf::Sprite sprite;
};

#endif HPP_PLANET