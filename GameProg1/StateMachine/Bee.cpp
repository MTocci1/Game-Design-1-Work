#include "Bee.hpp"
#include "BeeStates.hpp"

using sf::Time;
using sf::Vector2f;

// TODO Start the Bee in the idle state

Bee::Bee(Vector2f const& center, Vector2f const& position)
    : GameSprite("graphics/bee.png", position), center(center), currentState(new Bee::idleState(*this))
{
    // TODO Enter the current state if one exists
    if (currentState != nullptr) 
    {
        currentState->enter();
    }
}

void
Bee::onNotify(TriggerEvent const& event)
{
    // TODO Let the current state handle the event and change state if appropriate

    // is next state is different from current state?
    // if so exit the current state
    // set the next state as my current state
    // and enter the current state
    State* nextState = currentState->handleEvent(event);

    if (nextState != currentState) {
        // Exit the current state if it's not nullptr
        if (currentState != nullptr) {
            currentState->exit();
        }

        // Update the current state and enter the new state if it's not nullptr
        currentState = nextState;
        if (currentState != nullptr) {
            currentState->enter();
        }
    }

}

void
Bee::update(Time const& dt)
{
    // TODO Update the current state
    currentState->update(dt.asSeconds());

    if (velocity.x == 0 && velocity.y == 0) { return; }

    Vector2f prevPosition = sprite.getPosition();
    Vector2f newPosition = prevPosition + dt.asSeconds() * speed * velocity;
    sprite.setPosition(newPosition);
}
