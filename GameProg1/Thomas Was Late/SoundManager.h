#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
private:
	// The buffers
	SoundBuffer m_FireBuffer;
	SoundBuffer m_FallInFireBuffer;
	SoundBuffer m_FallInWaterBuffer;
	SoundBuffer m_JumpBuffer;
	SoundBuffer m_ReachGoalBuffer;
	SoundBuffer m_level1Buffer;
	SoundBuffer m_level2Buffer;
	SoundBuffer m_level3Buffer;
	SoundBuffer m_level4Buffer;
	SoundBuffer m_fireNarratorBuffer;
	SoundBuffer m_waterNarratorBuffer;
	SoundBuffer m_fallNarratorBuffer;

	// The Sounds
	Sound m_Fire1Sound;
	Sound m_Fire2Sound;
	Sound m_Fire3Sound;
	Sound m_FallInFireSound;
	Sound m_FallInWaterSound;
	Sound m_JumpSound;
	Sound m_ReachGoalSound;
	Sound m_level1Sound;
	Sound m_level2Sound;
	Sound m_level3Sound;
	Sound m_level4Sound;
	Sound m_fireNarratorSound;
	Sound m_waterNarratorSound;
	Sound m_fallNarratorSound;

	// Which sound should we use next, fire 1, 2 or 3
	int m_NextSound = 1;
public:
	SoundManager();

	void playFire(Vector2f emitterLocation,
		Vector2f listenerLocation);

	void playFallInFire();

	void playFallInWater();

	void playJump();

	void playReachGoal();

	void playLevel1();

	void playLevel2();

	void playLevel3();

	void playLevel4();

	void playFallOffMap();
};