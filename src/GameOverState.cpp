#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameOverState.h"
#include "GameState.h"
#include "TextCreator.h"
#include "GameConfig.h"

GameOverState::GameOverState(RenderWindow& windowRef, ValueGetter& valueGetterRef, GameConfig& gameConfigRef)
	: GameState(windowRef, valueGetterRef), gameConfig(gameConfigRef)
{
	valueGetter.attachLevelDataObserver(this);
	init();
}


void GameOverState::init()
{
	font.loadFromFile("resources/fonts/Cartoon Blocks Christmas.otf"); 

	TextCreator textCreator(50, 0);
	gameOverText = textCreator.createNewText(window, font, GAME_OVER_LABEL, TextAlignment::TOP_CENTER, gameOverTextSize);

	Vector2f posBelowGameOverText = gameOverText->getPosition() + Vector2f(0, gameOverText->getLocalBounds().height + verticalTextSpacing);
	totalScoreText = textCreator.createNewText(font, SCORE_LABEL + std::to_string(totalScore), posBelowGameOverText, scoreTextSize, TextOrigin::TOP_CENTER);

	restartButton = Button(RESTART_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
	menuButton = Button(MENU_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);

	restartButton.setButtonPosition(restartButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(menuButtonPosition, buttonTextOffset);

}

void GameOverState::onStateEnter()
{
	totalScoreText->setString(SCORE_LABEL + std::to_string(totalScore));
}

void GameOverState::handleInput()
{
	if (restartButton.buttonInteract(window))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::PLAYING_STATE;
		gameConfig.setLevel(currentMode);
	}

	if (menuButton.buttonInteract(window))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::MAIN_MENU;
		gameConfig.setLevel(currentMode);
	}
}

void GameOverState::update(float deltaTime)
{
}

void GameOverState::draw()
{
	window.draw(*gameOverText);
	window.draw(*totalScoreText);

	restartButton.drawButton(window);
	menuButton.drawButton(window);
}

void GameOverState::onStateExit()
{
	totalScore = 0;
}

void GameOverState::attachValueObserver(NumValueObserver* observer)
{
}

void GameOverState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}

void GameOverState::onValueChanged(int value, ValueType valueType)
{
	if (valueType == ValueType::SCORE)
	{
		totalScore = value;
	}
}

void GameOverState::onLevelChanged()
{
	switch (currentMode)
	{
	case LoadLevelMode::PROGRESS:
		break;

	case LoadLevelMode::RESET_LEVEL:
		if (nextState == State::PLAYING_STATE)
		{
			for (const auto& observer : stateObservers)
				observer->onStateChanged(State::PLAYING_STATE);
		}
		else
		{
			for (const auto& observer : stateObservers)
				observer->onStateChanged(State::MAIN_MENU);
		}
		break;

	case LoadLevelMode::RESET_GAME:
		break;

	default:
		break;
	}
	
}
