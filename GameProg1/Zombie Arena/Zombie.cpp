#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;


void Zombie::spawn(float startX, float startY, int type, int seed)
{
	m_Type = type;

	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		m_Speed = 40;
		m_Health = 5;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		m_Speed = 70;
		m_Health = 2;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		m_Speed = 20;
		m_Health = 3;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
{
	m_Health--;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// Increase crawler speed if shot
	if (m_Type == 1)
	{
		retreatTime = 3.0;
	}

	// Increase crawler speed if shot
	if (m_Type == 2) 
	{
		m_Speed += 30.0;
	}

	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime,
	Vector2f playerLocation, int& numZombiesAlive)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the Bloater zombie position variables
	if (m_hittingWall)
	{
		if (m_Type == 0 && m_Health > 1) {
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}
		}
	}

	if (!m_hittingWall)
	{
		if (m_Type == 0 && m_Health > 1) {
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}
		}
	}

	// Make bloater stop for 5 seconds then explode, if on 1 health
	if (m_Type == 0 && m_Health == 1)
	{
		bloaterExplodeTime -= elapsedTime;
	}

	// if 5 seconds have passed, then explode
	if (bloaterExplodeTime <= 0)
	{
		hit();
		numZombiesAlive -= 1;
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));
	}

	if (m_hittingWall)
	{
		// Update the Chaser zombie position variables
		if ((m_Type == 1 && m_Health == 2) || (m_Type == 1 && m_Health == 1 && retreatTime <= 0) || (m_Type == 1 && m_Health == 0 && retreatTime <= 0))
		{
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}
		}
	}

	if (!m_hittingWall)
	{
		// Update the Chaser zombie position variables
		if ((m_Type == 1 && m_Health == 2) || (m_Type == 1 && m_Health == 1 && retreatTime <= 0) || (m_Type == 1 && m_Health == 0 && retreatTime <= 0))
		{
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}
		}
	}

	// Update retreat time
	if ((m_Type == 1 && m_Health == 1) || (m_Type == 1 && m_Health == 0))
	{
		retreatTime -= elapsedTime;
	}

	if (m_hittingWall)
	{
		// Make the chaser retreat if shot
		if ((m_Type == 1 && m_Health == 1 && retreatTime > 0) || (m_Type == 1 && m_Health == 0 && retreatTime > 0))
		{
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}
		}
	}

	if (!m_hittingWall)
	{
		// Make the chaser retreat if shot
		if ((m_Type == 1 && m_Health == 1 && retreatTime > 0) || (m_Type == 1 && m_Health == 0 && retreatTime > 0))
		{
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}
		}
	}


	if (m_hittingWall)
	{
		// Update the Crawler zombie position variables
		if (m_Type == 2)
		{
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}
		}
	}

	if (!m_hittingWall)
	{
		// Update the Crawler zombie position variables
		if (m_Type == 2)
		{
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}
		}
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}

void Zombie::hasHitWall(bool isZombieHittingWall)
{
	m_hittingWall = isZombieHittingWall;
}