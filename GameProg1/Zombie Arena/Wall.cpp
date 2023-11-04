#include "Wall.h"
#include "TextureHolder.h"

Wall::Wall()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/wall.png"));
}

void Wall::setArena(IntRect arena)
{

	// Copy the details of the arena to the walls's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Wall::spawn()
{
	// Calculate the center of the arena
	int centerX = m_Arena.left + m_Arena.width / 2;
	int centerY = m_Arena.top + m_Arena.height / 2;

	// Ensure walls do not spawn in center (where player spawns)
	int centerRangeX = m_Arena.width / 8;
	int centerRangeY = m_Arena.height / 8;

	// Spawn walls in randomly outside the center range
	int x, y;
	do {
		x = m_Arena.left + (rand() % m_Arena.width - 50);
		y = m_Arena.top + (rand() % m_Arena.height - 50);
	} while (abs(x - centerX) < centerRangeX && abs(y - centerY) < centerRangeY);

	m_Spawned = true;

	m_Sprite.setPosition(x, y);
}

FloatRect Wall::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Wall::getSprite()
{
	return m_Sprite;
}

bool Wall::isSpawned()
{
	return m_Spawned;
}

FloatRect Wall::getCollider() const
{
	return m_Sprite.getGlobalBounds();
}

void Wall::update(float elapsedTime)
{

}