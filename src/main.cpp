#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game/Game.h"
#include "game/GameStateManager.h"
#include "audio/SoundPlayer.h" 

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Breakout");
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition(
		(desktop.width - window.getSize().x) / 2,
		(desktop.height - window.getSize().y) / 2
	);

	//LevelLoader levelLoader;
	//ValueGetter valueGetter(levelLoader);
	//CollisionManager collisionManager(window);
	//MusicPlayer audioPlayer(valueGetter);
	//SoundPlayer soundPlayer(valueGetter);
	//LevelDataProvider levelDataProvider;
	//ThemeManager themeManager;

	//BrickPool brickPool(valueGetter);
	//BrickGrid grid(valueGetter, brickPool, collisionManager);

	//Game game(window, valueGetter, brickPool, grid, levelLoader, audioPlayer, collisionManager, levelDataProvider, themeManager);
	Game game(window);
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

			gameStateManager.handleInput(event);
		}

		gameStateManager.update(deltaTime);
		gameStateManager.draw();

		window.display();
		window.clear();
	}

}