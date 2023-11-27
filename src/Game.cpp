#include <SFML/Graphics.hpp>
#include "Game.h"
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"
#include "Ball.h"
#include "BrickGrid.h"
#include "BrickGridVisual.h"
#include "ValueGetter.h"
#include <iostream>

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef)
	: window(windowRef), valueGetter(valueGetterRef), grid(gridRef)
{
	//should be able to change path from constructor!

	//Create objects
	auto gridVisual = std::make_unique<BrickGridVisual>(window, valueGetter, grid);
	auto platform = std::make_unique<Platform>(window, valueGetter);	
	auto ball = std::make_unique<Ball>(window, valueGetter, *platform, *gridVisual);
	
	//if you change the order here, 
	gameObjects.push_back(std::move(gridVisual));
	gameObjects.push_back(std::move(platform)); 
	gameObjects.push_back(std::move(ball));

}

//destructor needed I think, if you will use new Game for each level?

void Game::startGame()
{
	auto ball = static_cast<Ball*>(gameObjects[2].get());
	ball->toggleBounce();
}

void Game::restartGame()
{
	auto ball = static_cast<Ball*>(gameObjects[2].get());
	ball->toggleBounce();
	ball->setInitialBallPosition();
}

void Game::update(float deltaTime)
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->update(deltaTime);
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

