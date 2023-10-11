#include "Bee.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

// Define an enum class for direction
enum class Direction { Clockwise, CounterClockwise };

int main()
{
	// Create a video mode object
	VideoMode vm(500, 500);
	// Create and open a window for the game
	RenderWindow window(vm, "Lab3", Style::Fullscreen);



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

	// Create a bee
	Bee bee(textureBee);

	// Create a view with a size of 1024x1024 to match the background
	View view(Vector2f(512, 512), Vector2f(1024, 1024));
	window.setView(view);

	// Initialize the direction to clockwise
	Direction movementDirection = Direction::Clockwise;

	bool acceptInput = false;
	Clock clock;
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
					bee.moveCounterClockwise();
					acceptInput = false;
				}
				else
				{
					movementDirection = Direction::Clockwise;
					bee.moveClockwise();
					acceptInput = false;
				}
			}
		}
		/*
		*****************************************
		Update the scene
		*****************************************
		*/

		// All updates done in bee class
		// Update the delta time
		Time dt = clock.restart();
		bee.update(dt);

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
		window.draw(bee.spriteBee);
		window.display();
	}
	return 0;
}