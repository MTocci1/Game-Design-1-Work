#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Lava
{
private:

	// The sprite that represents this pickup
	Sprite m_Sprite;

	// The arena it exists in
	IntRect m_Arena;

	// Handle spawning and disappearing
	bool m_Spawned;


	// Public prototypes go here
public:

	Lava();

	// Prepare a new pickup
	void setArena(IntRect arena);

	void spawn();

	// Check the position of a wall
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned();

};