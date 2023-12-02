#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "XmlParser.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "BrickPool.h"



using namespace sf;


int main()
{
	XmlParser parser;
	std::string fileName = "Level_1";
	ValueGetter valueGetter(parser, fileName);
	BrickPool brickPool(valueGetter);
	BrickGrid grid(valueGetter, brickPool);


	// WINDOW
	RenderWindow window(VideoMode(700, 500), "Breakout"); //adjust 
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
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			default:
				break;
			}

			game.handleInput();


			if (Keyboard::isKeyPressed(Keyboard::Key::G)) //testing only
				grid.setLevelFinished();
		}


		game.update(deltaTime);
		game.draw();

		window.display();
		window.clear();

	}
}