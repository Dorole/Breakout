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
#include "CollisionManager.h"
#include "LevelDataProvider.h"

int main()
{
	//ovo sve sibni u jedan class tipa GameManager i od tamo pozovi

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Breakout");  
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition(
		(desktop.width - window.getSize().x) / 2,
		(desktop.height - window.getSize().y) / 2
	);

	LevelLoader levelLoader;
	ValueGetter valueGetter(levelLoader);
	CollisionManager collisionManager(window);
	MusicPlayer audioPlayer(valueGetter);
	LevelDataProvider levelDataProvider;
	
	BrickPool brickPool(valueGetter);
	BrickGrid grid(valueGetter, brickPool, collisionManager);

	Game game(window, valueGetter, grid, levelLoader, audioPlayer, collisionManager, levelDataProvider);
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