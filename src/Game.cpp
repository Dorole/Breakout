#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "GameState.h"
#include "PlayingState.h"

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef)
	: window(windowRef), valueGetter(valueGetterRef), grid(gridRef)
{
	std::cout << "Game constructor" << std::endl;
	currentState = std::make_shared<PlayingState>(window, valueGetter, grid);

	currentState->attachObserver(this);
}

void Game::changeStete(std::shared_ptr<GameState> newState)
{
	currentState = newState;
}

void Game::handleInput()
{
	currentState->handleInput();
}

void Game::update(float deltaTime)
{
	currentState->update(deltaTime);
}

void Game::draw()
{
	currentState->draw();
}




void Game::attachObserver(NumValueObserver* observer)
{
	observers.push_back(observer);
}

void Game::onValueChanged(int value, ValueType valueType)
{
	for (const auto& observer : observers)
	{
		observer->onValueChanged(value, valueType);
	}
}

