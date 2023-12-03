#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayingState.h"
#include "GameState.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "UIManager.h"
#include "GameObject.h"
#include "BrickGridVisual.h"
#include "Platform.h"
#include "Ball.h"
#include "NumValueObserver.h"


PlayingState::PlayingState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef)
	: GameState(windowRef, valueGetterRef), grid(gridRef)
{
	std::cout << "PlayingState ctr" << std::endl;

	init();
}


void PlayingState::init()
{
	std::cout << "PlayingState init" << std::endl;

	grid.attachObserver(this);

	//Create objects
	auto gridVisual = std::make_unique<BrickGridVisual>(window, valueGetter, grid, grid.getGridDataVector());
	auto platform = std::make_unique<Platform>(window, valueGetter);
	auto ball = std::make_unique<Ball>(window, valueGetter, *platform, grid, grid.getGridDataVector());

	ball->attachObserver(this);

	gameObjects.push_back(std::move(gridVisual));
	gameObjects.push_back(std::move(platform));
	gameObjects.push_back(std::move(ball));	

	uiManager = std::make_unique<UIManager>(window, valueGetter);
	attachValueObserver(uiManager.get());
	
}

void PlayingState::onStateEnter()
{
	totalScore = 0;
	currentLives = maxLives;
	gameStarted = false;

	for (const auto& observer : valueObservers)
	{
		observer->onValueChanged(totalScore, ValueType::SCORE);
		observer->onValueChanged(currentLives, ValueType::LIVES);
	}
}

void PlayingState::handleInput()
{
	if (Mouse::isButtonPressed(Mouse::Left)) 
		startGame();

	if (Mouse::isButtonPressed(Mouse::Right)) //DEBUG ONLY
		restartGame();

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
		std::cout << "GAME OVER" << std::endl;
		
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::GAME_OVER);
	}

	if (grid.allBricksDestroyed())
	{
		std::cout << "LEVEL FINISHED." << std::endl; 

		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::LEVEL_CLEAR);
	}

	uiManager->update();
}

void PlayingState::draw()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->draw();
	}

	uiManager->draw();

}

void PlayingState::onStateExit()
{
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
	ball->toggleBounce();
	ball->setInitialBallPosition();
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
