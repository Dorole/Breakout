#include "GameOverState.h"

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "MusicPlayer.h"
#include "TextCreator.h"
#include "LevelLoader.h"

GameOverState::GameOverState(RenderWindow& windowRef, ValueGetter& valueGetterRef, MusicPlayer& audioPlayerRef, LevelLoader& levelLoaderRef)
	: GameState(windowRef, valueGetterRef, audioPlayerRef), levelLoader(levelLoaderRef)
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

void GameOverState::setTextElements()
{
	font.loadFromFile(valueGetter.getDefaultFontPath());

	TextCreator textCreator(50, 0);
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
	restartButton = Button(RESTART_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
	menuButton = Button(MENU_TEXT, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);

	restartButton.setButtonOutline(1.0f, textColor);
	menuButton.setButtonOutline(1.0f, textColor);

	restartButton.setButtonPosition(restartButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(menuButtonPosition, buttonTextOffset);
}
