#include "PlayingState.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "BrickGrid.h"
#include "UIManager.h"
#include "GameObject.h"
#include "BrickGridVisual.h"
#include "Platform.h"
#include "Ball.h"
#include "NumValueObserver.h"


PlayingState::PlayingState(Game& game)
	: GameState(game), grid(game.getGrid()), colMan(game.getCollisionManager())
{
	grid.attachGridObserver(this);
	init(game);
}

void PlayingState::init(Game& game)
{
	//Create objects
	auto gridVisual = std::make_unique<BrickGridVisual>(game, grid.getGridDataVector());
	auto platform = std::make_unique<Platform>(game);
	auto ball = std::make_unique<Ball>(game, grid.getGridDataVector());

	ball->attachObserver(this);

	gameObjects.push_back(std::move(gridVisual));
	gameObjects.push_back(std::move(platform));
	gameObjects.push_back(std::move(ball));

	uiManager = std::make_unique<UIManager>(window, valueGetter);
	attachValueObserver(uiManager.get());
}

void PlayingState::onStateEnter()
{
	setBackground(valueGetter.getBackgroundTexturePath());

	totalScore = 0;
	currentLives = maxLives;
	gameStarted = false;

	for (const auto& observer : valueObservers)
	{
		observer->onValueChanged(totalScore, ValueType::SCORE);
		observer->onValueChanged(currentLives, ValueType::LIVES);
	}

	audioPlayer.loadPlayMusic(AudioType::LEVEL_MUSIC);

	colMan.mapCollidables();
}

void PlayingState::handleInput()
{
	if (Mouse::isButtonPressed(Mouse::Left)) 
		startGame();

	uiManager->handleInput();
}

void PlayingState::update(float deltaTime)
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->update(deltaTime);
	}

	if (currentLives == 0)
	{	
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::GAME_OVER);
	}

	if (grid.allBricksDestroyed())
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::LEVEL_CLEAR);
	}

	colMan.update();
	uiManager->update();
}

void PlayingState::draw()
{
	window.draw(bgImage);

	for (auto& gameObject : gameObjects)
	{
		gameObject->draw();
	}

	uiManager->draw();

}

void PlayingState::onStateExit()
{
	restartGame();

	audioPlayer.stopMusic();

}

void PlayingState::startGame()
{
	if (gameStarted || currentLives == 0) return;

	auto ball = static_cast<Ball*>(gameObjects[2].get());
	ball->toggleBounce();

	gameStarted = true;
}

void PlayingState::restartGame()
{
	auto ball = static_cast<Ball*>(gameObjects[2].get());
	if (ball->getShouldBounce())
		ball->toggleBounce();
	ball->resetBallPosition();
}



void PlayingState::updateScore(int amount)
{
	totalScore += amount;
}

void PlayingState::updateLives(int amount)
{
	currentLives -= amount;
}


void PlayingState::attachValueObserver(NumValueObserver* observer)
{
	valueObservers.push_back(observer);
}

void PlayingState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}

void PlayingState::onBrickDestroyed(Brick& brick)
{
	updateScore(brick.getBreakScore());

	for (const auto& observer : valueObservers)
		observer->onValueChanged(totalScore, ValueType::SCORE);
}

// handles lost life - maybe separate function for that so we know what's up
void PlayingState::onValueChanged(int value, ValueType valueType)
{
	if (valueType != ValueType::LIVES) return;

	gameStarted = false;
	updateLives(value);
	restartGame();

	for (const auto& observer : valueObservers)
		observer->onValueChanged(currentLives, ValueType::LIVES);
}

void PlayingState::setTextElements(){}

void PlayingState::setButtonElements(){}

