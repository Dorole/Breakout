#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

#include "XmlParser.h"
#include "ValueGetter.h"
#include "BrickSoft.h"

using namespace sf;


int main()
{
	XmlParser parser;
	std::string fileName = "Level_1";
	ValueGetter valueGetter(parser, fileName);
	BrickSoft softBrick(valueGetter);

	// WINDOW
	RenderWindow window(VideoMode(1060, 1000), "Breakout"); //adjust - SHOULD BE WAY SMALLER
	window.setPosition({ 650, 150 });

	Game game(window, valueGetter);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.update();
		game.render();
	}
}