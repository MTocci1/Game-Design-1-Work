#include "Wall.h"
#include "TextureHolder.h"

Wall::Wall()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/wall.png"));
}

void Wall::setArena(IntRect arena)
{

	// Copy the details of the arena to the pickup's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Wall::spawn()
{
	// Spawn at a random location
	int x = m_Arena.left + (rand() % m_Arena.width - 50);
	int y = m_Arena.top + (rand() % m_Arena.height -50);

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

void Wall::update(float elapsedTime)
{

}