// Include important libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// Make code easier to type with "using namespace"
using namespace sf;
// This is where our game starts from
// Function declaration
void updateBranches(int seed, int deathsUnder10Seconds, int deathsOver10Seconds);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
// Where is the player/branch?
// left or right?
enum class side { LEFT, RIGHT, MIDDLE, NONE };
side branchPositions[NUM_BRANCHES];
int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	// Create a texture to hold a graphic on the GPU
	Texture tectureBackground;
	// Load a graphics into the texture
	tectureBackground.loadFromFile("graphics/background.png");
	// Create a sprite
	Sprite spriteBackground;
	// Attach the texture to the sprite
	spriteBackground.setTexture(tectureBackground);
	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);
	// Make a pillar sprite
	Texture texturePillar;
	texturePillar.loadFromFile("graphics/pillar.png");
	Sprite spritePillar;
	spritePillar.setTexture(texturePillar);
	spritePillar.setPosition(810, 0);

	// Prepare the goose
	Texture textureGoose;
	textureGoose.loadFromFile("graphics/goose.png");
	Sprite spriteGoose;
	spriteGoose.setTexture(textureGoose);
	spriteGoose.setPosition(0, 800);
	//Is the goose currently moving?
	bool gooseActive = false;

	//How fast can the goose fly
	float gooseSpeedX = 400.0f;
	float gooseSpeedY = -400.0f;

	// make 3 cloud sprites from 1 texture
	Texture textureCloud;
	// Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");
	// 3 New sprites with the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	// Position the clouds on the left of the screen
	// at different heights
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	// How fast is each cloud?
	// Set speeds for diagonal movement
	float cloud1SpeedX = 100.0f;
	float cloud1SpeedY = -100.0f;

	// Straght line
	float cloud2Speed = 0.0f;

	// Diagonal
	float cloud3SpeedX = 100.0f;
	float cloud3SpeedY = -100.0f;

	// Variables to control time itself
	Clock clock;
	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	// Track whether the game is running
	bool paused = true;
	// Draw some text
	int score = 0;
	Text messageText;
	Text scoreText;
	// We need to choose a font
	Font font;
	font.loadFromFile("fonts/Crang.ttf");
	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);
	// Prepare 6 Branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		// Set the sprites origin to dead center
		// we can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}
	// Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	// The player starts on the left
	side playerSide = side::LEFT;
	// Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);
	// Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line the axe up with the pillar
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1200;
	const float AXE_POSITION_MIDDLE = 1050.5;

	// Prepare the flying piece
	Texture texturePiece;
	texturePiece.loadFromFile("graphics/piece.png");
	Sprite spritePiece;
	spritePiece.setTexture(texturePiece);
	spritePiece.setPosition(810, 720);
	// Some other useful piece related variables
	bool pieceActive = false;
	float pieceSpeedX = 1000;
	float pieceSpeedY = -1500;
	// Control the player input
	bool acceptInput = false;
	// Prepare the sounds
	// The player chopping sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	// The player has met his end under a branch
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	// Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	// Variables for invincibility ability
	bool isInvincible = false;
	float invincibilityDuration = 5.0f;
	float invincibilityCooldown = 30.0f;
	float invincibilityTimer = 0.0f;
	bool canUseInvincibility = true;
	
	// Display the invinsibility timers
	Text invincibilityTimerText;
	Text invincibilityCooldownText;

	invincibilityTimerText.setFont(font);
	invincibilityCooldownText.setFont(font);

	invincibilityTimerText.setCharacterSize(40);
	invincibilityCooldownText.setCharacterSize(40);

	invincibilityTimerText.setFillColor(Color::White);
	invincibilityCooldownText.setFillColor(Color::White);

	invincibilityTimerText.setPosition(1300, 20);
	invincibilityCooldownText.setPosition(1500, 60);

	// Variables for dynamic difficulty
	float playerAliveTime = 0.0f;
	int deathsUnder10Seconds = 0;
	int deathsOver10Seconds = 0;

	while (window.isOpen())
	{
		/*
		******************************************
		Handle players input
		******************************************
		*/
		// Start the game
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;
				// hide the axe
				spriteAxe.setPosition(3000,
					spriteAxe.getPosition().y);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return)) 
		{
			paused = false;
			// Reset the time and the score
			score = 0;
			timeRemaining = 6;

			// Reset invincibility timer and cooldown
			canUseInvincibility = true;
			invincibilityTimer = 0.0f;
			invincibilityCooldown = 30.0f;


			// Make all the branches disappear -
			// starting in the second position
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}
			// Make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);
			// Move the player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}
		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;
				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(180);
				spritePlayer.setPosition(1100, 720);
				// Update the branches
				updateBranches(score, deathsUnder10Seconds, deathsOver10Seconds);

				// Set the piece flying to the left
				spritePiece.setPosition(810, 720);
				pieceSpeedX = -5000;
				pieceActive = true;
				acceptInput = false;
				// Play a chop sound
				chop.play();
			}
			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;
				score++;
				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(0);
				spritePlayer.setPosition(620, 735);
				// update the branches
				updateBranches(score, deathsUnder10Seconds, deathsOver10Seconds);
				// set the piece flying
				spritePiece.setPosition(810, 720);
				pieceSpeedX = 5000;
				pieceActive = true;
				acceptInput = false;
				// Play a chop sound
				chop.play();
			}

			// Added Middle position for the player
			// Handle pressing the down arrow key
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				// Make sure the player is on the right
				playerSide = side::MIDDLE;

				score++;
				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_MIDDLE,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(180);
				spritePlayer.setPosition(960, 720);
				// Update the branches
				updateBranches(score, deathsUnder10Seconds, deathsOver10Seconds);

				// Set the piece flying to the left
				spritePiece.setPosition(810, 720);
				pieceSpeedX = -5000;
				pieceActive = true;
				acceptInput = false;
				// Play a chop sound
				chop.play();
			}
			// Activate invincibility
			if (canUseInvincibility && Keyboard::isKeyPressed(Keyboard::Space)) {
				isInvincible = true;
				invincibilityTimer = invincibilityDuration;
				canUseInvincibility = false;
			}
		}

		/*
		*****************************************
		Update the scene
		*****************************************
		*/
		if (!paused)
		{
			// Measure time
			Time dt = clock.restart();
			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			// Keep track of how long the player is alive
			playerAliveTime += dt.asSeconds();

			// Size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f) {
				// Since player didn't die, increase the difficulty
				deathsOver10Seconds ++;

				//Pause the game
				paused = true;
				// Change the message shown to the player
					messageText.setString("Out of time!");
				// Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				// Play the out of time sound
				outOfTime.play();
			}

			// Update invincibility timer
			if (isInvincible) {
				invincibilityTimer -= dt.asSeconds();
				// If timer reaches 0 player is no longer invinsible
				if (invincibilityTimer <= 0.0f) {
					isInvincible = false;
				}
			}
			// Update invincibility cooldown time
			else if (!canUseInvincibility) {
				invincibilityCooldown -= dt.asSeconds();
				// If cooldown reaches 0 allow user to use ability again
				if (invincibilityCooldown <= 0.0f) {
					canUseInvincibility = true;
					invincibilityCooldown = 30.0f;
				}
			}
			
			// The goose now moves diagonally, starts in the bottom right, and the starting height and speed is random
			// Setup the goose
			if (!gooseActive)
			{
				// How fast is the goose on x axis
				srand((int)time(0));
				gooseSpeedX = (rand() % 200) + 200;

				// How fast is the goose on y axis 
				srand((int)time(0));
				gooseSpeedY = -1 * ((rand() % 200) + 200);

				//How high is the goose
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;

				// Set the goose's starting position
				spriteGoose.setPosition(1920, height);
				gooseActive = true;
			}
			else
				//Move the goose
			{
				// Update goose position
				spriteGoose.setPosition(
					spriteGoose.getPosition().x - (gooseSpeedX * dt.asSeconds()),
					spriteGoose.getPosition().y + (gooseSpeedY * dt.asSeconds())
				);

				// Check if the goose is off-screen
				if (spriteGoose.getPosition().x < -100 || spriteGoose.getPosition().y < -100)
				{
					gooseActive = false;
				}
			}
			// Manage the clouds
			// Cloud 1
			// Made it so it moves up and to the right diagonally
			if (!cloud1Active)
			{
				// Set cloud1's starting position off-screen to the right
				spriteCloud1.setPosition(1920, 540);
				cloud1Active = true;
			}
			else
			{
				// Update cloud1 position diagonally up and to the left
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x - (cloud1SpeedX * dt.asSeconds()),
					spriteCloud1.getPosition().y + (cloud1SpeedY * dt.asSeconds())
				);

				// Check if cloud1 is off-screen
				if (spriteCloud1.getPosition().x < -200 || spriteCloud1.getPosition().y < -200)
				{
					cloud1Active = false;
				}
			}
			// Cloud 2
			// Made it so it will always have the same starting position
			if (!cloud2Active)
			{
				// How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);
				// How high is the cloud
				spriteCloud2.setPosition(-200, 200);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);
				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud2Active = false;
				}
			}
			// Cloud 3
			// Made it so it move up and to the left diagonally
			if (!cloud3Active)
			{
				// Set cloud 3's starting position off-screen to the left
				spriteCloud3.setPosition(-200, 540);
				cloud3Active = true;
			}
			else
			{
				// Update cloud 3 position diagonally up and to the right
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud3SpeedX * dt.asSeconds()),
					spriteCloud3.getPosition().y + (cloud3SpeedY * dt.asSeconds())
				);

				// Check if cloud 3 is off-screen
				if (spriteCloud3.getPosition().x > 1920 || spriteCloud3.getPosition().y < -200)
				{
					cloud3Active = false;
				}
			}
			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			// Update the invinsibility timer and cooldown text
			std::stringstream timerText;
			timerText << "Invincibility Timer: " << static_cast<int>(invincibilityTimer) << "s";

			std::ostringstream cooldownText;
			cooldownText << "Cooldown: " << static_cast<int>(invincibilityCooldown) << "s";

			invincibilityTimerText.setString(timerText.str());
			invincibilityCooldownText.setString(cooldownText.str());

			// update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(590, height);
					// Flip the sprite round the other way
					branches[i].setRotation(180);
					// Scale to normal size
					branches[i].setScale(1.0f, 1.0f);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setRotation(0);
					branches[i].setScale(1.0f, 1.0f);
				}
				else if (branchPositions[i] == side::MIDDLE)
				{
					// Move the sprite to the middle
					branches[i].setPosition(1020, height);
					// Set the sprite rotation to normal
					branches[i].setRotation(30);
					// Scale down so it stays in middle
					branches[i].setScale(0.5f, 0.5f);
				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}
			// Handle a flying piece
			if (pieceActive)
			{
				spritePiece.setPosition(
					spritePiece.getPosition().x +
					(pieceSpeedX * dt.asSeconds()),

					spritePiece.getPosition().y +
					(pieceSpeedY * dt.asSeconds()));
				// Has the piece reached the right hand edge?
				if (spritePiece.getPosition().x < -100 ||
					spritePiece.getPosition().x > 2000)
				{
					// Set it up ready to be a whole new piece next frame
					pieceActive = false;
					spritePiece.setPosition(810, 720);
				}
			}
			// has the player been squished by a branch?
			if (!isInvincible && branchPositions[5] == playerSide)
			{
				// death
				paused = true;
				acceptInput = false;
				canUseInvincibility = true;
				invincibilityTimer = 0.0f;
				invincibilityCooldown = 30.0f;


				// If player lived more than 10 seconds increase the difficulty
				if (playerAliveTime >= 10.0f) {
					deathsOver10Seconds ++;
					playerAliveTime = 0;
				}
				// If not, decrease difficulty
				else {
					deathsUnder10Seconds ++;
					playerAliveTime = 0;

				}

				// Draw the gravestone
				spriteRIP.setPosition(625, 760);
				// hide the player
				spritePlayer.setPosition(2000, 660);
				// Change the text of the message
				messageText.setString("SQUISHED!!");
				// Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f,
					1080 / 2.0f);
				// Play the death sound
				death.play();
			}
		} // End if (!paused)
		/*
		*****************************************
		Draw the scene
		*****************************************
		*/
		// Clear everything from the last frame
		window.clear();
		// Draw our game scene here
		window.draw(spriteBackground);
		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		// Draw the pillar
		window.draw(spritePillar);
		//Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		// Draw the flying piece
		window.draw(spritePiece);
		// Draw the player
		window.draw(spritePlayer);
		// Draw the axe
		window.draw(spriteAxe);
		// Draw the gravestone
		window.draw(spriteRIP);
		// Draw the Goose
		window.draw(spriteGoose);
		// Draw the score
		window.draw(scoreText);
		// Draw the invinibility timers
		window.draw(invincibilityTimerText);
		window.draw(invincibilityCooldownText);
		// Draw the timebar
		window.draw(timeBar);
		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}
		// Show everything we just drew
		window.display();
	}
	return 0;
}
// update the branches, also take into account player performance
void updateBranches(int seed, int deathsUnder10Seconds, int deathsOver10Seconds)
{
	// Calculate the difference in deaths to adjust the probability of NONE
	int deathDifference = deathsUnder10Seconds - deathsOver10Seconds;

	// Set the default probability of no branches
	float noneProbability = 0.2f;

	if (deathDifference >= 0)
	{
		// Increase probability when deathDifference is positive
		noneProbability += 0.1f * deathDifference;
	}
	else
	{
		// Decrease probability when deathDifference is negative
		noneProbability -= 0.1f * abs(deathDifference);
	}

	// Ensure noneProbability does not exceed 80%
	noneProbability = std::min(0.8f, noneProbability);

	// Ensure noneProbability does not go below 0%
	noneProbability = std::max(0.0f, noneProbability);

	// Ensure probability stays within bounds (0 to 1)
	noneProbability = std::max(0.0f, std::min(1.0f, noneProbability));

	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at position 0
	// Left, Right, Middle, or None
	srand((int)time(0) + seed);
	float r = (rand() % 100) / 100.0f;

	if (r < noneProbability)
	{
		branchPositions[0] = side::NONE;
	}
	else
	{
		srand((int)time(0) + seed);
		int randomValue = rand() % 3;
		if (randomValue == 0)
		{
			branchPositions[0] = side::LEFT;
		}
		else if (randomValue == 1)
		{
			branchPositions[0] = side::RIGHT;
		}
		// Added MIDDLE position for branch
		else
		{
			branchPositions[0] = side::MIDDLE;
		}
	}
}
