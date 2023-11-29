#include "PlayableCharacterStates.h"

#include <iostream>

using sf::Sprite;
using sf::Vector2f;

PlayableCharacter::State::State(PlayableCharacter& character) : controlledCharacter(character) {}

// TODO Implement your derives PlayableCharacter states here
// ...

// Jumping State
PlayableCharacter::jumpingState::jumpingState(PlayableCharacter& character) : PlayableCharacter::State(character) {}

void PlayableCharacter::jumpingState::enter()
{
    std::cout << "Enter jumping state\n";
    
}

PlayableCharacter::State* PlayableCharacter::jumpingState::handleEvent()
{
    // check value of the trigger event
    // and then decide what state to return
    if (controlledCharacter.m_IsJumping == true) {
        return this;
    }
    if (controlledCharacter.m_IsFalling == true) {
        return new PlayableCharacter::fallingState(controlledCharacter);
    }
    if (controlledCharacter.m_IsFalling == false && controlledCharacter.m_IsJumping == false) {
        return new PlayableCharacter::stillState(controlledCharacter);
    }
    return nullptr;
}

void PlayableCharacter::jumpingState::exit()
{
    std::cout << "Exit jumping state\n";
}

void PlayableCharacter::jumpingState::update(float dt)
{

	// Update how long the jump has been going
	controlledCharacter.m_TimeThisJump += dt;

	// Is the jump going upwards
	if (controlledCharacter.m_TimeThisJump < controlledCharacter.m_JumpDuration)
	{
		// Move up at twice gravity
        controlledCharacter.m_Position.y -= controlledCharacter.m_Gravity * 2 * dt;
	}
	else
	{
        controlledCharacter.m_IsJumping = false;
        controlledCharacter.m_IsFalling = true;
	}

}

//Falling State
PlayableCharacter::fallingState::fallingState(PlayableCharacter& character) : PlayableCharacter::State(character) {}

void PlayableCharacter::fallingState::enter()
{
    std::cout << "Enter falling state\n";
    
}

PlayableCharacter::State* PlayableCharacter::fallingState::handleEvent()
{
    // check value of the trigger event
    // and then decide what state to return
    if (controlledCharacter.m_IsFalling == true) {
        return this;
    }
    if (controlledCharacter.m_IsJumping == true) {
        return new PlayableCharacter::jumpingState(controlledCharacter);
    }
    if (controlledCharacter.m_IsFalling == false && controlledCharacter.m_IsJumping == false) {
        return new PlayableCharacter::stillState(controlledCharacter);
    }
    return nullptr;
}

void PlayableCharacter::fallingState::exit()
{
    std::cout << "Exit falling state\n";
}

void PlayableCharacter::fallingState::update(float dt)
{
    controlledCharacter.m_Position.y += controlledCharacter.m_Gravity * dt;
}

//Still State
PlayableCharacter::stillState::stillState(PlayableCharacter& character) : PlayableCharacter::State(character) {}

void PlayableCharacter::stillState::enter()
{
    std::cout << "Enter still state\n";

}

PlayableCharacter::State* PlayableCharacter::stillState::handleEvent()
{
    // check value of the trigger event
    // and then decide what state to return
    if (controlledCharacter.m_IsFalling == false && controlledCharacter.m_IsJumping == false) {
        return this;
    }
    if (controlledCharacter.m_IsFalling == true) {
        return new PlayableCharacter::fallingState(controlledCharacter);
    }
    if (controlledCharacter.m_IsJumping == true) {
        return new PlayableCharacter::jumpingState(controlledCharacter);
    }
    return nullptr;
}

void PlayableCharacter::stillState::exit()
{
    std::cout << "Exit still state\n";
}

void PlayableCharacter::stillState::update(float dt){}


