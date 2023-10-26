#include "CollisionCounter.hpp"

using namespace sf;

CollisionCounter::CollisionCounter(Font const& font, Vector2f const& pos)
    : text("0", font, 48u), count(0)
{
    text.setPosition(pos);
}

void CollisionCounter::draw(RenderWindow& target) const
{
    target.draw(text);
}

void CollisionCounter::onNotify(::Event const& ev) {
    if (ev.name == "CollisionEvent") {
        // Increment the collision count
        count++;

        // Update the text
        text.setString(std::to_string(count));
    }
}
