#include "Lava.h"
#include "TextureHolder.h"

Lava::Lava()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/lava.png"));
}

void Lava::setArena(IntRect arena)
{

	// Copy the details of the arena to the lava's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Lava::spawn()
{
	// Spawn at a random location
	int x = m_Arena.left + (rand() % m_Arena.width - 50);
	int y = m_Arena.top + (rand() % m_Arena.height - 50);

	m_Spawned = true;

	m_Sprite.setPosition(x, y);
}

FloatRect Lava::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Lava::getSprite()
{
	return m_Sprite;
}

bool Lava::isSpawned()
{
	return m_Spawned;
}

void Lava::update(float elapsedTime)
{

}