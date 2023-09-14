#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

// Define an enum class for direction
enum class Direction { Clockwise, CounterClockwise};

int main()
{
	// Create a video mode object
	VideoMode vm(500, 500);
	// Create and open a window for the game
	RenderWindow window(vm, "Lab2", Style::Fullscreen);
	// Create a texture to hold a graphic on the GPU
	Texture tectureBackground;
	// Load a graphics into the texture
	tectureBackground.loadFromFile("graphics/grass.png");
	// Create a sprite
	Sprite spriteBackground;
	// Attach the texture to the sprite
	spriteBackground.setTexture(tectureBackground);
	// Set the background sprite to cover the screen
	spriteBackground.setPosition(0, 0);
	// Make a flower sprite
	Texture textureFlower;
	textureFlower.loadFromFile("graphics/sunflower.png");
	Sprite spriteFlower;
	spriteFlower.setTexture(textureFlower);
	spriteFlower.setPosition(280, 280);
	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	// Center of the circle around which the bee will move
	float circleCenterX = 450.0f;
	float circleCenterY = 450.0f; 
	float radius = 200.0f; 
	// Set the initial angle
	float angle = 0.0f;

	// Set bee position to the center of the circle
	spriteBee.setPosition(circleCenterX, circleCenterY);

	// Create a view with a size of 1024x1024 to match the background
	View view(Vector2f(512, 512), Vector2f(1024, 1024));
	window.setView(view);

	// Initialize the direction to clockwise
	Direction movementDirection = Direction::Clockwise;

	bool acceptInput = false;

	while (window.isOpen())
	{
		/*
		******************************************
		Handle players input
		******************************************
		*/
		
		// Ensure the user has released the spacebar
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				// Listen for key presses again
				acceptInput = true;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		// Make sure we are accepting input
		if (acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (movementDirection == Direction::Clockwise)
				{
					movementDirection = Direction::CounterClockwise;
					acceptInput = false;
				}
				else
				{
					movementDirection = Direction::Clockwise;
					acceptInput = false;
				}
			}
		}
		/*
		*****************************************
		Update the scene
		*****************************************
		*/

		float beeX;
		float beeY;

		if (movementDirection == Direction::Clockwise)
		{
			// Move the bee in a clockwise direction
			beeX = circleCenterX + radius * std::cos(angle);
			beeY = circleCenterY + radius * std::sin(angle);
			angle += 0.01f;
		}
		else
		{
			// Move the bee in a counter-clockwise direction, set the angle to negative
			beeX = circleCenterX + radius * std::cos(-angle);
			beeY = circleCenterY + radius * std::sin(-angle);
			angle += 0.01f;
		}

		spriteBee.setPosition(beeX, beeY);

		/*
		*****************************************
		Draw the scene
		*****************************************
		*/
		// Clear everything from the last frame
		window.clear();
		// Draw our game scene here
		window.draw(spriteBackground);
		// Draw the Flower
		window.draw(spriteFlower);
		// Draw the Bee
		window.draw(spriteBee);
		window.display();
	}
	return 0;
}