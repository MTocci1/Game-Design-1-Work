#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
	// How fast is each zombie type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	float CRAWLER_SPEED = 20;

	// How tough is each zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 2;
	const float CRAWLER_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

	int m_Type;

	// New bloater variables
	float bloaterExplodeTime = 5.0;
	bool didExplode = false;

	// New Chaser Variable
	float retreatTime = 3.0;

	bool m_hittingWall;

	// When was the zombie last hit by lava
	Time m_LastHit;

	// What size is the current arena
	IntRect m_Arena;

	// How big is each tile of the arena
	int m_TileSize;

	// Public prototypes go here	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	// Handle when zombie steps in lava
	bool hitByLava(Time timeHit);

	// How long ago was the zombie last hit by lava
	Time getLastHitTime();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed, IntRect arena, int tileSize);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation, int& numZombiesAlive);

	// check if zombie is hitting wall
	void hasHitWall(bool isZombieHittingWall);
};