#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "LevelClearState.h"

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef)
	: window(windowRef), valueGetter(valueGetterRef), grid(gridRef)
{
	std::cout << "Game constructor" << std::endl;

	mainMenuState = std::make_shared<MainMenuState>(window, valueGetter);
	playingState = std::make_shared<PlayingState>(window, valueGetter, grid);
	gameOverState = std::make_shared<GameOverState>(window, valueGetter);
	levelClearState = std::make_shared<LevelClearState>(window, valueGetter);

	currentState = mainMenuState;

	//save states in a local vector (?)
	//loop through all states and attach itself

	mainMenuState->attachStateObserver(this);
	playingState->attachStateObserver(this);
	gameOverState->attachStateObserver(this);
	levelClearState->attachStateObserver(this);

	GameOverState* gameOverState_ptr = dynamic_cast<GameOverState*>(gameOverState.get());
	LevelClearState* levelClearState_ptr = dynamic_cast<LevelClearState*>(levelClearState.get());
	playingState->attachValueObserver(gameOverState_ptr);
	playingState->attachValueObserver(levelClearState_ptr);

}

void Game::changeState(std::shared_ptr<GameState> newState)
{
	currentState->onStateExit();

	currentState = newState;
	currentState->onStateEnter();
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

void Game::onStateChanged(State state)
{
	switch (state)
	{
	case State::MAIN_MENU:
		changeState(mainMenuState);
		break;
	case State::PLAYING_STATE:
		changeState(playingState);
		break;
	case State::GAME_OVER:
		changeState(gameOverState);
		break;
	case State::LEVEL_CLEAR:
		changeState(levelClearState);
		break;
	default:
		break;
	}
}

