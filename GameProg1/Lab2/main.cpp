#include <SFML/Graphics.hpp>
using namespace sf;

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
	spriteBee.setPosition(30, 30);
	//Is the bee currently moving?
	bool beeActive = false;
	//How fast can the bee fly
	float beeSpeed = 0.0f;

	// Create a view with a size of 1024x1024 to match the background
	View view(Vector2f(512, 512), Vector2f(1024, 1024));
	window.setView(view);

	while (window.isOpen())
	{
		/*
		******************************************
		Handle players input
		******************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		*****************************************
		Update the scene
		*****************************************
		*/


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