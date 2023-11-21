#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int main()
{
	// WINDOW
	RenderWindow window(VideoMode(1060, 1000), "Breakout"); //adjust - SHOULD BE WAY SMALLER
	window.setPosition({ 650, 150 });

	Game game(window);

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