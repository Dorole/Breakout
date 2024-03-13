#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "LevelLoader.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "Game.h"
#include "BrickGrid.h"
#include "BrickPool.h"
#include "GameStateManager.h"

int main()
{
	//Game je trenutno dosta useless - vidi sto s tim
	//ovo sve sibni u jedan class tipa GameManager i od tamo pozovi

	LevelLoader levelLoader;
	ValueGetter valueGetter(levelLoader);
	MusicPlayer audioPlayer(valueGetter);

	BrickPool brickPool(valueGetter);
	BrickGrid grid(valueGetter, brickPool);

	// WINDOW
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Breakout");  
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition(
		(desktop.width - window.getSize().x) / 2,
		(desktop.height - window.getSize().y) / 2
	);

	Game game(window, valueGetter, grid, levelLoader, audioPlayer);
	GameStateManager gameStateManager(game);
	
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gameStateManager.handleInput();
		}

		gameStateManager.update(deltaTime);
		gameStateManager.draw();

		window.display();
		window.clear();
	}

}