#include "GameOverState.h"

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameState.h"
#include "MusicPlayer.h"
#include "TextCreator.h"
#include "LevelLoader.h"

GameOverState::GameOverState(Game& game)
	: GameState(game), levelLoader(game.getLevelLoader())
{
	valueGetter.attachLevelDataObserver(this);
	init();
}


void GameOverState::init()
{
	setBackground("resources/textures/night_forest_rabbit.png");
	setTextElements();
	setButtonElements();
}

void GameOverState::onStateEnter()
{
	totalScoreText->setString(SCORE_LABEL + std::to_string(totalScore));

	audioPlayer.loadPlayMusic(AudioType::GAME_OVER_MUSIC);
}

void GameOverState::handleInput()
{
	if (restartButton.buttonInteract(window))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::PLAYING_STATE;
		levelLoader.setLevel(currentMode);
	}

	if (menuButton.buttonInteract(window))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::MAIN_MENU;
		levelLoader.setLevel(currentMode);

		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::MAIN_MENU);
	}
}

void GameOverState::update(float deltaTime)
{
}

void GameOverState::draw()
{
	window.draw(bgImage);

	window.draw(*gameOverText);
	window.draw(*totalScoreText);

	restartButton.drawButton(window);
	menuButton.drawButton(window);
}

void GameOverState::onStateExit()
{
	totalScore = 0;
	audioPlayer.stopMusic();
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
	if (nextState == State::PLAYING_STATE)
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::PLAYING_STATE);
	}
}

void GameOverState::setTextElements()
{
	font.loadFromFile(valueGetter.getDefaultFontPath());

	float gameOverTextSize = window.getSize().y * gameOverTextPercentage / 100.0f;
	float scoreTextSize = window.getSize().y * scoreTextPercentage / 100.0f;
	float topOffset = window.getSize().y * gameOverTextTopOffsetPercentage / 100.0f;
	float verticalTextSpacing = window.getSize().y * verticalTextSpacingPercentage / 100.0f;

	TextCreator textCreator(topOffset, 0);
	gameOverText = textCreator.createNewText(window, font, GAME_OVER_LABEL, TextAlignment::TOP_CENTER, gameOverTextSize);
	gameOverText->setOutlineThickness(0.1f);
	gameOverText->setOutlineColor(Color::White);

	Vector2f posBelowGameOverText = gameOverText->getPosition() + Vector2f(0, gameOverText->getLocalBounds().height + verticalTextSpacing);
	totalScoreText = textCreator.createNewText(font, SCORE_LABEL + std::to_string(totalScore), posBelowGameOverText, scoreTextSize, TextOrigin::TOP_CENTER);
	totalScoreText->setOutlineThickness(0.1f);
	totalScoreText->setOutlineColor(Color::White);
}

void GameOverState::setButtonElements()
{
	float buttonWidth = window.getSize().x * buttonWidthPercentage / 100.0f;
	float buttonHeight = window.getSize().y * buttonHeightPercentage / 100.0f;
	Vector2f buttonSize = Vector2f(buttonWidth, buttonHeight);

	float buttonTextSize = buttonHeight * buttonTextSizePercentage / 100.0f;

	float buttonSpacing = window.getSize().y * buttonSpacingPercentage / 100.0f;
	Vector2f restartButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
	Vector2f menuButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + buttonSize.y + buttonSpacing);

	restartButton = Button(RESTART_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
	menuButton = Button(MENU_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);

	restartButton.setButtonOutline(1.0f, textColor);
	menuButton.setButtonOutline(1.0f, textColor);

	restartButton.setButtonPosition(restartButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(menuButtonPosition, buttonTextOffset);
}
