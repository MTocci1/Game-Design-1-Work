#ifndef HPP_HUD
#define HPP_HUD

#include <SFML/Graphics.hpp>
#include "Observer.hpp"
#include "Event.hpp"

class CollisionCounter : public Observer {
public:
    CollisionCounter(sf::Font const& font, sf::Vector2f const& pos);
    void draw(sf::RenderWindow& target) const;
    void onNotify(::Event const& ev);
private:
    sf::Text text;
    int count;
};

#endif HPP_HUD
