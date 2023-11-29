#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "XmlParser.h"
#include "ValueGetter.h"
#include "BrickGrid.h"

#include "UIManager.h"


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
	UIManager uiManager(window, valueGetter);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (Mouse::isButtonPressed(Mouse::Left)) //disable doing this more than once
				game.startGame();

			if (Mouse::isButtonPressed(Mouse::Right)) //debug only
				game.restartGame();

			if (Keyboard::isKeyPressed(Keyboard::Key::G)) //testing only
				grid.setLevelFinished();
		}


		game.update(deltaTime);
		game.render();

		uiManager.draw();
	}
}