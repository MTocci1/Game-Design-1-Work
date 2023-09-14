#ifndef CPP_HELLO
#define CPP_HELLO

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std; // imports all symbols from the std namespace into the global namespace
using namespace sf;

int main()
{
	// << is called the stream insertion operator
	// >> is call the stream extraction operator
	cout << "Hello, World!" << endl;

	// RenderWindow constructor takes 3 arguments - VideoMode, string, Style
	RenderWindow window({ 500,250 }, "Lab 1", Style::Default);

	Font font;
	if (!font.loadFromFile("../../SFML-2.6.0/examples/opengl/resources/tuffy.ttf"))
		return 1;

	Text text("Hello World!", font, 75);
	text.setPosition(75, 75);

	while (true)
	{
		window.clear();
		window.draw(text);
		window.display();
	}
}
#endif CPP_HELLO