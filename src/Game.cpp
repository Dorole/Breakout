#include <SFML/Graphics.hpp>
#include "Game.h"
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"
#include "Ball.h"
#include "BrickGrid.h"
#include "ValueGetter.h"
#include "BrickGridVisual.h"

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef)
	: window(windowRef), valueGetter(valueGetterRef), grid(gridRef)
{
	//should be able to change path from constructor!

	//Create objects
	auto platform = std::make_unique<Platform>(window, valueGetter);
	auto ball = std::make_unique<Ball>(window, valueGetter, *platform);
	auto gridVisual = std::make_unique<BrickGridVisual>(window, valueGetter, grid);
	
	gameObjects.push_back(std::move(platform)); 
	gameObjects.push_back(std::move(ball));
	gameObjects.push_back(std::move(gridVisual));
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
		gameObject->draw();
	}

	window.display();
	window.clear();
}