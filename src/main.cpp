#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "LevelLoader.h"
#include "XmlParser.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "Game.h"
#include "BrickGrid.h"
#include "BrickPool.h"


using namespace sf;


int main()
{
	XmlParser parser;
	LevelLoader levelLoader;
	ValueGetter valueGetter(parser, levelLoader);
	MusicPlayer audioPlayer(valueGetter);

	BrickPool brickPool(valueGetter);
	BrickGrid grid(valueGetter, brickPool);

	// WINDOW
	RenderWindow window(VideoMode(1920, 1080), "Breakout"); //adjust 
	VideoMode desktop = VideoMode::getDesktopMode();
	Vector2i windowPosition(
		(desktop.width - window.getSize().x) / 2,
		(desktop.height - window.getSize().y) / 2
	);

	Game game(window, valueGetter, grid, levelLoader, audioPlayer);
	
	Clock clock;
	float deltaTime;

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