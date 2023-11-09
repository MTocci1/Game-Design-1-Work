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

void Bee::orbitState::update(float dt) {}

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

void Bee::wanderState::update(float dt) {}

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
