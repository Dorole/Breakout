#include <SFML/Graphics.hpp>
#include "Game.h"
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "ValueGetter.h"

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef)
	: window(windowRef), valueGetter(valueGetterRef)
{
	//should be able to change path from constructor!

	//Create objects
	auto platform = std::make_unique<Platform>(window, valueGetter);
	gameObjects.push_back(std::move(platform)); //pazi ako planiras jos koristiti platform, sad je platform nullptr! --> push_back direktno

	BrickGrid grid(valueGetter);
}

void Game::update()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->update();
	}
}

void Game::render()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->draw(window);
	}

	window.display();
	window.clear();
}