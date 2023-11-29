#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// Load a level
		loadLevel();
	}
	if (m_Playing)
	{
		// Update Thomas
		if (m_Thomas.isSpawned()) 
		{
			m_Thomas.update(dtAsSeconds);
		}
		
		// Update Bob
		m_Bob.update(dtAsSeconds);

		// Update Rob
		if (m_Rob.isSpawned()) {
			m_Rob.update(dtAsSeconds);
		}

		// Detect collisions and see if characters 
		// have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (m_Thomas.isSpawned()) {
			if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
			{
				// New level required
				m_NewLevelRequired = true;
				// Play the reach goal sound    
			}
			else
			{
				// Run bobs collision detection
				detectCollisions(m_Bob);
			}

			// Let bob and thomas jump on each others heads
			if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
			{
				m_Bob.stopFalling(m_Thomas.getHead().top);
			}
			else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
			{
				m_Thomas.stopFalling(m_Bob.getHead().top);
			}
		}

		// Detect collisions and see if characters 
		// have reached the goal tile
		// The second part of the if condition is only executed
		// when rob is touching the home tile
		if (m_Rob.isSpawned()) {
			if (detectCollisions(m_Rob) && detectCollisions(m_Bob))
			{
				// New level required
				m_NewLevelRequired = true;
				// Play the reach goal sound    
			}
			else
			{
				// Run bobs collision detection
				detectCollisions(m_Bob);
			}

			// Let bob and Rob jump on each others heads
			if (m_Bob.getFeet().intersects(m_Rob.getHead()))
			{
				m_Bob.stopFalling(m_Rob.getHead().top);
			}
			else if (m_Rob.getFeet().intersects(m_Bob.getHead()))
			{
				m_Rob.stopFalling(m_Bob.getHead().top);
			}
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();
		}
	}// End if playing

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emitter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.isSpawned()) {
			if (m_Thomas.getPosition().intersects(localRect))
			{
				// Play the sound and pass in the location as well
				m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
			}
		}

		// Is the player inside localRect?
		if (m_Rob.isSpawned()) {
			if (m_Rob.getPosition().intersects(localRect))
			{
				// Play the sound and pass in the location as well
				m_SM.playFire(Vector2f(posX, posY), m_Rob.getCenter());
			}
		}
	}

	// Set the appropriate view around the appropriate character
	if (m_SplitScreen)
	{
		if (m_Thomas.isSpawned()) {
			m_LeftView.setCenter(m_Thomas.getCenter());
		}
		if (m_Rob.isSpawned()) {
			m_LeftView.setCenter(m_Rob.getCenter());
		}
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		// Center full screen around appropriate character
		if (m_Character1)
		{
			if (m_Thomas.isSpawned()) {
				m_MainView.setCenter(m_Thomas.getCenter());
			}
			if (m_Rob.isSpawned()) {
				m_MainView.setCenter(m_Rob.getCenter());
			}
		}
		else
		{
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}
	// Time to update the HUD?
	// Increment the number of frames since 
   // the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		stringstream ssTime;

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}