#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "GameConfig.h"
#include "XmlParser.h"
#include "ValueGetter.h"
#include "Game.h"
#include "BrickGrid.h"
#include "BrickPool.h"



using namespace sf;


int main()
{
	GameConfig gameConfig;
	XmlParser parser;

	ValueGetter valueGetter(parser, gameConfig.getFileName(0));
	BrickPool brickPool(valueGetter);
	BrickGrid grid(valueGetter, brickPool);


	// WINDOW
	RenderWindow window(VideoMode(700, 500), "Breakout"); //adjust 
	window.setPosition({ 650, 150 });

	Clock clock;
	float deltaTime;

	Game game(window, valueGetter, grid, gameConfig);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Key::G && event.key.control && event.key.alt)
				{
					std::cout << "Cheat code for level clearing used." << std::endl;
					grid.setLevelFinished();
				}
				break;
			default:
				break;
			}

			game.handleInput();
		}

		game.update(deltaTime);
		game.draw();

		window.display();
		window.clear();

	}
}