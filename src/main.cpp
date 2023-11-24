#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"

#include "XmlParser.h"
#include "ValueGetter.h"
#include "BrickSoft.h"
#include "BrickGrid.h"
#include "BrickHard.h"
#include "BrickMedium.h"
#include "BrickImpenetrable.h"

using namespace sf;


int main()
{
	XmlParser parser;
	std::string fileName = "Level_1";
	ValueGetter valueGetter(parser, fileName);
	BrickGrid grid(valueGetter);

	// WINDOW
	RenderWindow window(VideoMode(700, 500), "Breakout"); //adjust - SHOULD BE WAY SMALLER
	window.setPosition({ 650, 150 });

	Game game(window, valueGetter, grid);

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