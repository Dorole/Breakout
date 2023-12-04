#include <iostream>
#include <SFML/Graphics.hpp>
#include "LevelClearState.h"
#include "GameState.h"
#include "TextCreator.h"
#include "Button.h"
#include "GameConfig.h"

LevelClearState::LevelClearState(RenderWindow& windowRef, ValueGetter& valueGetterRef, GameConfig& gameConfigRef)
	: GameState(windowRef, valueGetterRef), gameConfig(gameConfigRef)
{
	valueGetter.attachLevelDataObserver(this);
	init();
}

void LevelClearState::init()
{
	font.loadFromFile("resources/fonts/Cartoon Blocks Christmas.otf"); //from config

	TextCreator textCreator(30, 0);
	levelClearText = textCreator.createNewText(window, font, LEVEL_CLEAR_LABEL, TextAlignment::TOP_CENTER, levelClearTextSize);

	Vector2f posBelowGameOverText = levelClearText->getPosition() + Vector2f(0, levelClearText->getLocalBounds().height + verticalTextSpacing);
	totalScoreText = textCreator.createNewText(font, SCORE_LABEL + std::to_string(totalScore), posBelowGameOverText, scoreTextSize, TextOrigin::TOP_CENTER);

	nextButton = Button(NEXT_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
	restartButton = Button(RESTART_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
	menuButton = Button(MENU_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);

	nextButton.setButtonPosition(nextButtonPosition, buttonTextOffset);
	restartButton.setButtonPosition(restartButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(menuButtonPosition, buttonTextOffset);
}

void LevelClearState::onStateEnter()
{
	totalScoreText->setString(SCORE_LABEL + std::to_string(totalScore));
}

void LevelClearState::handleInput()
{
	if (nextButton.buttonInteract(window))
	{
		currentMode = LoadLevelMode::PROGRESS;
		nextState = State::PLAYING_STATE;
		gameConfig.setLevel(currentMode);
	}

	if (restartButton.buttonInteract(window))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::PLAYING_STATE;
		gameConfig.setLevel(currentMode);
	}

	if (menuButton.buttonInteract(window))
	{
		if (gameConfig.nextLevelExists())
			currentMode = LoadLevelMode::RESET_LEVEL;
		else
			currentMode = LoadLevelMode::RESET_GAME;

		nextState = State::MAIN_MENU;
		gameConfig.setLevel(currentMode);
	}
}

void LevelClearState::update(float deltaTime)
{
}

void LevelClearState::draw()
{
	window.draw(*levelClearText);
	window.draw(*totalScoreText);

	if (gameConfig.nextLevelExists())
	{
		nextButton.drawButton(window);
	}

	restartButton.drawButton(window);
	menuButton.drawButton(window);
}

void LevelClearState::onStateExit()
{
	totalScore = 0;
}

void LevelClearState::attachValueObserver(NumValueObserver* observer)
{
}

void LevelClearState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}

void LevelClearState::onValueChanged(int value, ValueType valueType)
{
	if (valueType == ValueType::SCORE)
	{
		totalScore = value;
	}
}


void LevelClearState::onLevelChanged()
{
	switch (currentMode)
	{
	case LoadLevelMode::PROGRESS:
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::PLAYING_STATE);
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
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::MAIN_MENU);
		break;

	default:
		break;
	}
}
