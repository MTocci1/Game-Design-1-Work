#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Pong", Style::Fullscreen);

	// Create a view with a size of 1920 x 1080 to match the background regardless of natve resolution
	View view(Vector2f(960, 540), Vector2f(1920, 1080));
	window.setView(view);

	int score = 0;
	int lives = 3;
	float gameTime = 0.0f;

	// Variables for slow ability
	float slowCooldown = 15.0f;
	float slowDuration = 5.0f;
	float slowTimer = 0.0f;
	bool isSlowActive = false;
	bool canUseSlow = true;

	// Set up new sounds
	// Ball hiting bat sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sounds/hit.mp3");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// Intro music
	SoundBuffer introBuffer;
	introBuffer.loadFromFile("sounds/intro_music.mp3");
	Sound intro;
	intro.setBuffer(introBuffer);

	// Stage 2 music
	SoundBuffer speedUpBuffer;
	speedUpBuffer.loadFromFile("sounds/speed_up.mp3");
	Sound speedUp;
	speedUp.setBuffer(speedUpBuffer);

	// Max Speed music
	SoundBuffer maxSpeedBuffer;
	maxSpeedBuffer.loadFromFile("sounds/max_speed.mp3");
	Sound maxSpeed;
	maxSpeed.setBuffer(maxSpeedBuffer);

	// Ensure each sound plays only once per game
	bool introPlayed = false;
	bool speedUpPlayed = false;
	bool maxSpeedPlayed = false;

	// Prepare the bat
	Texture textureBat;
	textureBat.loadFromFile("graphics/bat.png");
	// Create a bat at the bottom center of the screen
	Bat bat(0 + 20, 1080 / 2, 0 + 20, 200, 0, 1030, textureBat);

	// Prepare the ball
	Texture textureBall;
	textureBall.loadFromFile("graphics/ball.png");
	// Create a ball
	Ball ball(1920, 1080 /2, textureBall);

	// Create Text objects HUD and timerText
	Text hud;
	Text timerText;
	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/ka1.ttf");
	// Set the font to our retro-style
	hud.setFont(font);
	timerText.setFont(font);
	// Make it nice and big
	hud.setCharacterSize(75);
	timerText.setCharacterSize(25);
	// Choose a color
	hud.setFillColor(Color::White);
	timerText.setFillColor(Color::White);
	hud.setPosition(1020, 20);
	timerText.setPosition(1340, 1040);

	// Here is our clock for timing everything
	Clock clock;
	while (window.isOpen())
	{
		/*
		Handle the player input
		****************************
		****************************
		****************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when the window is closed
				window.close();
		}
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			bat.moveUp();
		}
		else
		{
			bat.stopUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			bat.moveDown();
		}
		else
		{
			bat.stopDown();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}
		// Activate Slow
		// Handle the pressing and releasing of spacebar
		if (canUseSlow && Keyboard::isKeyPressed(Keyboard::Space))
		{
			isSlowActive = true;
			slowTimer = slowDuration;
			canUseSlow = false;
			ball.slow();
		}

		/*	
		Update the bat, the ball and the HUD
		*****************************
		*****************************
		*****************************
		*/
		// Update the delta time
		Time dt = clock.restart();
		gameTime += dt.asSeconds();
		
		bat.update(dt);
		ball.update(dt);

		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << "  Lives:" << lives;
		hud.setString(ss.str());

		// Update timerText
		std::stringstream timers;
		timers << "Slow Timer: " << static_cast<int>(slowTimer) << "s " << "Cooldown: " << static_cast<int>(slowCooldown) << "s";
		timerText.setString(timers.str());

		// Handle ball hitting the bottom
		if (ball.getPosition().left < 0)
		{
			// Play a hit sound
			hit.play();
			// reverse the ball direction
			ball.reboundBottom();
			// Remove a life
			lives--;
			// Check for zero lives
			if (lives < 1) {
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
				// Pause other sounds before playing
				intro.stop();
				speedUp.stop();
				maxSpeed.stop();
				// Reset everything for next game
				canUseSlow = true;
				introPlayed = false;
				speedUpPlayed = false;
				maxSpeedPlayed = false;
				gameTime = 0;
				ball.resetSpeed();
			}
		}

		// Handle ball hitting top
		if (ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			// Play a hit sound
			hit.play();
			ball.reboundTop();
			// Add a point to the players score
			score++;
		}

		// Handle ball hitting sides
		if (ball.getPosition().top < 0 ||
			ball.getPosition().top > window.getSize().y)
		{
			hit.play();
			ball.reboundSides();
		}

		// Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			hit.play();
			ball.hitBat();
		}

		// Update slow timer
		if (isSlowActive)
		{
			slowTimer -= dt.asSeconds();
			// If timer reaches 0 ball is no longer slow
			if (slowTimer <= 0.0f)
			{
				isSlowActive = false;
				ball.endSlow();
			}
		}
		// Update slow cooldown time
		else if (!canUseSlow)
		{
			slowCooldown -= dt.asSeconds();
			// If cooldown reaches 0 allow user to use ability again
			if (slowCooldown <= 0.0f)
			{
				canUseSlow = true;
				slowCooldown = 15.0f;
			}
		}

		// Game Music (longer a game is played, more intense the music)
		// Check if it's time to play the intro sound
		if (!introPlayed && gameTime >= 0.0f)
		{
			intro.play();
			introPlayed = true;
		}

		// Check if it's time to play the speedUp sound
		if (!speedUpPlayed && gameTime >= 45.0f)
		{
			// Pause other sounds before playing
			intro.pause();
			maxSpeed.pause();

			speedUp.play();
			speedUpPlayed = true;
		}

		// Check if it's time to play the maxSpeed sound
		if (!maxSpeedPlayed && gameTime >= 95.0f)
		{
			// Pause other sounds before playing
			intro.pause();
			speedUp.pause();

			maxSpeed.play();
			maxSpeedPlayed = true;
		}

		/*
		Draw the bat, the ball and the HUD	
		*****************************
		*****************************
		*****************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(timerText);
		window.draw(bat.spriteBat);
		window.draw(ball.spriteBall);
		window.display();

	}
	return 0;
}