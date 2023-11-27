#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "XmlParser.h"
#include "ValueGetter.h"
#include "BrickGrid.h"



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

	Clock clock;
	float deltaTime;

	Game game(window, valueGetter, grid);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (Mouse::isButtonPressed(Mouse::Left))
				game.startGame();

			if (Mouse::isButtonPressed(Mouse::Right)) //debug only
				game.restartGame();
		}


		game.update(deltaTime);
		game.render();
	}
}