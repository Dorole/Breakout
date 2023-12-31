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


PlayingState::PlayingState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, MusicPlayer& audioPlayerRef, BrickGrid& gridRef)
	: GameState(windowRef, valueGetterRef, audioPlayerRef), grid(gridRef)
{
	grid.attachObserver(this);
	init();
}

void PlayingState::init()
{
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

	std::cout << "Entered level" << std::endl;
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

void PlayingState::setTextElements(){}

void PlayingState::setButtonElements(){}
