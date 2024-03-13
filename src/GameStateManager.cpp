#include "GameStateManager.h"
#include <iostream>

#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "LevelClearState.h"

using namespace sf;

GameStateManager::GameStateManager(Game& game)
{
	mainMenuState = std::make_shared<MainMenuState>(game);
	playingState = std::make_shared<PlayingState>(game);
	gameOverState = std::make_shared<GameOverState>(game);
	levelClearState = std::make_shared<LevelClearState>(game);

	currentState = mainMenuState;
	currentState->onStateEnter();

	mainMenuState->attachStateObserver(this);
	playingState->attachStateObserver(this);
	gameOverState->attachStateObserver(this);
	levelClearState->attachStateObserver(this);

	GameOverState* gameOverState_ptr = dynamic_cast<GameOverState*>(gameOverState.get());
	LevelClearState* levelClearState_ptr = dynamic_cast<LevelClearState*>(levelClearState.get());
	playingState->attachValueObserver(gameOverState_ptr);
	playingState->attachValueObserver(levelClearState_ptr);

}

void GameStateManager::changeState(std::shared_ptr<GameState> newState)
{
	if (currentState == newState) return;

	currentState->onStateExit();

	currentState = newState;
	currentState->onStateEnter();
}

void GameStateManager::handleInput()
{
	currentState->handleInput();

	if (currentState != playingState) return;

	if (Keyboard::isKeyPressed(Keyboard::Key::C)
		&& Keyboard::isKeyPressed(Keyboard::Key::LControl)
		&& Keyboard::isKeyPressed(Keyboard::Key::LAlt))
	{
		std::cout << "Cheat code for level clearing used." << std::endl;
		changeState(levelClearState);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::G)
		&& Keyboard::isKeyPressed(Keyboard::Key::LControl)
		&& Keyboard::isKeyPressed(Keyboard::Key::LAlt))
	{
		std::cout << "Cheat code for game over used." << std::endl;
		changeState(gameOverState);
	}
}

void GameStateManager::update(float deltaTime)
{
	currentState->update(deltaTime);
}

void GameStateManager::draw()
{
	currentState->draw();
}

void GameStateManager::attachObserver(NumValueObserver* observer)
{
	observers.push_back(observer);
}

void GameStateManager::onValueChanged(int value, ValueType valueType)
{
	for (const auto& observer : observers)
	{
		observer->onValueChanged(value, valueType);
	}
}

void GameStateManager::onStateChanged(State state)
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