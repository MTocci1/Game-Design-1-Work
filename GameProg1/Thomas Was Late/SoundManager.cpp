#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;
SoundManager::SoundManager()
{
	// Load the sound in to the buffers
	m_FireBuffer.loadFromFile("sound/fire1.wav");
	m_FallInFireBuffer.loadFromFile("sound/fallinfire.wav");
	m_FallInWaterBuffer.loadFromFile("sound/fallinwater.wav");
	m_JumpBuffer.loadFromFile("sound/jump.wav");
	m_ReachGoalBuffer.loadFromFile("sound/reachgoal.wav");
	m_level1Buffer.loadFromFile("sound/level1.mp3");
	m_level2Buffer.loadFromFile("sound/level2.mp3");
	m_level3Buffer.loadFromFile("sound/level3.mp3");
	m_level4Buffer.loadFromFile("sound/level4.mp3");
	m_fireNarratorBuffer.loadFromFile("sound/fire-narrator.mp3");;
	m_waterNarratorBuffer.loadFromFile("sound/water-narrator.mp3");;
	m_fallNarratorBuffer.loadFromFile("sound/fall-narrator.mp3");;

	// Associate the sounds with the buffers
	m_Fire1Sound.setBuffer(m_FireBuffer);
	m_Fire2Sound.setBuffer(m_FireBuffer);
	m_Fire3Sound.setBuffer(m_FireBuffer);
	m_FallInFireSound.setBuffer(m_FallInFireBuffer);
	m_FallInWaterSound.setBuffer(m_FallInWaterBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);
	m_level1Sound.setBuffer(m_level1Buffer);;
	m_level2Sound.setBuffer(m_level2Buffer);;
	m_level3Sound.setBuffer(m_level3Buffer);;
	m_level4Sound.setBuffer(m_level4Buffer);;
	m_fireNarratorSound.setBuffer(m_fireNarratorBuffer);;
	m_waterNarratorSound.setBuffer(m_waterNarratorBuffer);;
	m_fallNarratorSound.setBuffer(m_fallNarratorBuffer);;

	// When the player is 50 pixels away sound is full volume
	float minDistance = 150;

	// The sound reduces steadily as the player moves further away
	float attenuation = 15;

	// Set all the attenuation levels
	m_Fire1Sound.setAttenuation(attenuation);
	m_Fire2Sound.setAttenuation(attenuation);
	m_Fire3Sound.setAttenuation(attenuation);

	// Set all the minimum distance levels
	m_Fire1Sound.setMinDistance(minDistance);
	m_Fire2Sound.setMinDistance(minDistance);
	m_Fire3Sound.setMinDistance(minDistance);

	// Loop all the fire sounds
	// when they are played
	m_Fire1Sound.setLoop(true);
	m_Fire2Sound.setLoop(true);
	m_Fire3Sound.setLoop(true);

	m_JumpSound.setVolume(25);
	m_FallInFireSound.setVolume(25);
	m_FallInWaterSound.setVolume(25);
}

void SoundManager::playFire(
	Vector2f emitterLocation, Vector2f listenerLocation)
{
	// Where is the listener? Thomas.
	Listener::setPosition(listenerLocation.x,
		listenerLocation.y, 0.0f);
	switch (m_NextSound)
	{
	case 1:
		// Locate/move the source of the sound
		m_Fire1Sound.setPosition(emitterLocation.x,
			emitterLocation.y, 0.0f);
		if (m_Fire1Sound.getStatus() == Sound::Status::Stopped)
		{
			// Play the sound, if its not already
			m_Fire1Sound.play();
		}
		break;

	case 2:
		// Do the same as previous for the second sound
		m_Fire2Sound.setPosition(emitterLocation.x,
			emitterLocation.y, 0.0f);
		if (m_Fire2Sound.getStatus() == Sound::Status::Stopped)
		{
			m_Fire2Sound.play();
		}
		break;

	case 3:
		// Do the same as previous for the third sound
		m_Fire3Sound.setPosition(emitterLocation.x,
			emitterLocation.y, 0.0f);
		if (m_Fire3Sound.getStatus() == Sound::Status::Stopped)
		{
			m_Fire3Sound.play();
		}
		break;
	}

	// Increment to the next fire sound
	m_NextSound++;

	// Go back to 1 when the third sound has been started
	if (m_NextSound > 3)
	{
		m_NextSound = 1;
	}
}

void SoundManager::playFallInFire()
{
	m_FallInFireSound.setRelativeToListener(true);
	m_FallInFireSound.play();
	m_fireNarratorSound.play();
}

void SoundManager::playFallInWater()
{
	m_FallInWaterSound.setRelativeToListener(true);
	m_FallInWaterSound.play();
	m_waterNarratorSound.play();
}

void SoundManager::playJump()
{
	m_JumpSound.setRelativeToListener(true);
	m_JumpSound.play();
}

void SoundManager::playReachGoal()
{
	m_ReachGoalSound.setRelativeToListener(true);
	m_ReachGoalSound.play();
}

void SoundManager::playLevel1()
{
	m_level1Sound.play();
}

void SoundManager::playLevel2()
{
	m_level2Sound.play();
}

void SoundManager::playLevel3()
{
	m_level3Sound.play();
}

void SoundManager::playLevel4()
{
	m_level4Sound.play();
}

void SoundManager::playFallOffMap()
{
	m_fallNarratorSound.play();
}