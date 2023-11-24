#pragma once
#include "PlayableCharacter.h"

class Rob : public PlayableCharacter
{
public:
	// A constructor specific to Rob
	Rob();

	// The overriden input handler for Rob
	bool virtual handleInput();

	void virtual isOnSand(bool onSand);

};