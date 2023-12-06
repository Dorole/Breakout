#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "ValueGetter.h"
#include "BrickGrid.h"
#include "LevelLoader.h"
#include "MusicPlayer.h"
#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "LevelClearState.h"

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef, LevelLoader& levelLoaderRef, MusicPlayer& audioPlayerRef)
	: window(windowRef), valueGetter(valueGetterRef), grid(gridRef), levelLoader(levelLoaderRef), audioPlayer(audioPlayerRef)
{
	mainMenuState = std::make_shared<MainMenuState>(window, valueGetter, audioPlayer);
	playingState = std::make_shared<PlayingState>(window, valueGetter, audioPlayer, grid);
	gameOverState = std::make_shared<GameOverState>(window, valueGetter, audioPlayer, levelLoader);
	levelClearState = std::make_shared<LevelClearState>(window, valueGetter, audioPlayer, levelLoader);

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

void Game::changeState(std::shared_ptr<GameState> newState)
{
	if (currentState == newState) return;
	
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

