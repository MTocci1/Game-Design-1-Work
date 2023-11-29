#pragma once
#include "PlayableCharacter.h"

struct PlayableCharacter::State
{
	State(PlayableCharacter& character);
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual State* handleEvent() = 0;
	virtual void update(float dt) = 0;
	PlayableCharacter& controlledCharacter;
};

// TODO Declare the inner-structs for the Bee states here
struct PlayableCharacter::jumpingState : public PlayableCharacter::State {
	jumpingState(PlayableCharacter& character);
	void enter();
	void exit();
	State* handleEvent();
	void update(float dt);
};

struct PlayableCharacter::fallingState : public PlayableCharacter::State {
	fallingState(PlayableCharacter& character);
	void enter();
	void exit();
	State* handleEvent();
	void update(float dt);
};

struct PlayableCharacter::stillState : public PlayableCharacter::State {
	stillState(PlayableCharacter& character);
	void enter();
	void exit();
	State* handleEvent();
	void update(float dt);
};