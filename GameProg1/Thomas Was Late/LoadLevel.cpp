#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	if (m_LM.getCurrentLevel() == 1)
	{
		// Spawn Thomas and Bob
		m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Thomas.setSpawn(true);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.setSpawn(true);

		// Make sure rob does not spawn
		m_Rob.setSpawn(false);

		m_SM.playLevel1();
	}
	if (m_LM.getCurrentLevel() == 2)
	{
		// Spawn Thomas and Bob
		m_Rob.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Rob.setSpawn(true);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.setSpawn(true);

		m_Thomas.setSpawn(false);

		m_SM.playLevel2();
	}
	if (m_LM.getCurrentLevel() == 3)
	{
		// Spawn Thomas and Bob
		m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Thomas.setSpawn(true);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.setSpawn(true);

		// Make sure rob does not spawn
		m_Rob.setSpawn(false);

		m_SM.playLevel3();
	}
	if (m_LM.getCurrentLevel() == 4)
	{
		// Spawn Thomas and Bob
		m_Rob.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Rob.setSpawn(true);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.setSpawn(true);

		m_Thomas.setSpawn(false);

		m_SM.playLevel4();
	}

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}