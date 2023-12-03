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
		if (gameConfig.nextLevelExists())
		{
			gameConfig.progressLevel();
		}
		else
			std::cout << "Next level doesn't exist" << std::endl;
			//move to final state or main menu

	}

	if (restartButton.buttonInteract(window))
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::PLAYING_STATE);
	}

	if (menuButton.buttonInteract(window))
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::MAIN_MENU);
	}
}

void LevelClearState::update(float deltaTime)
{
	//shoul probably listen for an event from gameConfig
	/*for (const auto& observer : stateObservers)
	observer->onStateChanged(State::PLAYING_STATE);*/
}

void LevelClearState::draw()
{
	window.draw(*levelClearText);
	window.draw(*totalScoreText);

	nextButton.drawButton(window);
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
