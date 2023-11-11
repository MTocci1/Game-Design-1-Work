#include "BeeStates.hpp"
#include "Trigger.hpp"
#include "VectorMath.hpp"

#include <cmath>
#include <iostream>

using sf::Sprite;
using sf::Vector2f;

/* Forward declarations of auxiliary functions */

bool coinflip();
float random();

Bee::State::State(Bee& bee) : controlledBee(bee) {}

// TODO Implement your derives Bee states here
// ...

// Idle State
Bee::idleState::idleState(Bee& bee) : Bee::State(bee) {}

void Bee::idleState::enter()
{
    std::cout << "Enter idle state\n";
    // stop the bee moving make the velocity zero
    Bee::State::controlledBee.velocity.x = 0;
    Bee::State::controlledBee.velocity.y = 0;
}

void Bee::idleState::exit() 
{
    std::cout << "Exit idle state\n";
}

Bee::State* Bee::idleState::handleEvent(TriggerEvent const& ev)
{
    // check value of the trigger event
    // and then decide what state to return
    if (ev.value == 1) {
        return this;
    }
    if (ev.value == 2) {
        return new Bee::orbitState(controlledBee);
    }
    if (ev.value == 3) {
        return new Bee::wanderState(controlledBee);
    }
    return nullptr;
}

void Bee::idleState::update(float dt) {}

//Orbit State
Bee::orbitState::orbitState(Bee& bee) : Bee::State(bee) {}

void Bee::orbitState::enter()
{
    std::cout << "Enter orbit state\n";
    // stop the bee moving make the velocity zero
    Bee::State::controlledBee.velocity.x = 0;
    Bee::State::controlledBee.velocity.y = 0;
}

void Bee::orbitState::exit() 
{
    std::cout << "Exit orbit state\n";
}

Bee::State* Bee::orbitState::handleEvent(TriggerEvent const& ev)
{
    // check value of the trigger event
    // and then decide what state to return
    if (ev.value == 1) {
        return new Bee::idleState(controlledBee);
    }
    if (ev.value == 2) {
        return this;
    }
    if (ev.value == 3) {
        return new Bee::wanderState(controlledBee);
    }
    return nullptr;
}

void Bee::orbitState::update(float dt) 
{
    float rotationSpeed = 1.5f;
    float angle = rotationSpeed * dt;
    Vector2f currentPosition = controlledBee.sprite.getPosition() - controlledBee.center;

    // Rotate the current position
    float newX = currentPosition.x * cos(angle) - currentPosition.y * sin(angle);
    float newY = currentPosition.x * sin(angle) + currentPosition.y * cos(angle);

    // Set the new position relative to the center
    controlledBee.sprite.setPosition(controlledBee.center + Vector2f(newX, newY));
}

//Wander State
Bee::wanderState::wanderState(Bee& bee) : Bee::State(bee) {}

void Bee::wanderState::enter()
{
    std::cout << "Enter wander state\n";
    // stop the bee moving make the velocity zero
    Bee::State::controlledBee.velocity.x = 0;
    Bee::State::controlledBee.velocity.y = 0;
}

void Bee::wanderState::exit() 
{
    std::cout << "Exit wander state\n";
}

Bee::State* Bee::wanderState::handleEvent(TriggerEvent const& ev)
{
    // check value of the trigger event
    // and then decide what state to return
    if (ev.value == 1) {
        return new Bee::idleState(controlledBee);
    }
    if (ev.value == 2) {
        return new Bee::orbitState(controlledBee);
    }
    if (ev.value == 3) {
        return this;
    }
    return nullptr;
}

void Bee::wanderState::update(float dt) 
{
        // Check if the bee should change directions
        if (coinflip()) {
            // Generate random values for the x and y components of the velocity
            float randomVeloX = random();
            float randomVeloY = random();
            if (randomVeloX >= .5) {
                controlledBee.velocity.x = 1.0;
            }
            else {
                controlledBee.velocity.x = -1.0;
            }

            if (randomVeloY >= .5) {
                controlledBee.velocity.y = 1.0;
            }
            else {
                controlledBee.velocity.y = -1.0;
            }
        }

    // Update the position based on the velocity
    controlledBee.sprite.setPosition(
        controlledBee.sprite.getPosition().x + (dt * controlledBee.speed * controlledBee.velocity.x),
        controlledBee.sprite.getPosition().y + (dt * controlledBee.speed * controlledBee.velocity.y)
    );
}

/* Auxiliary functions */

bool
coinflip()
{
    constexpr static int HALF_MAX = RAND_MAX / 2;
    return rand() < HALF_MAX;
}

float
random()
{
    return rand() / float(RAND_MAX);
}
