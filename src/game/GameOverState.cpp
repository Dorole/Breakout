#include "GameOverState.h"
#include <SFML/Graphics.hpp>
#include "UI/TextCreator.h"

const std::string GameOverState::GAME_OVER_IMAGE = "GameOverImage";
const std::string GameOverState::GAME_OVER_LABEL = "GAME OVER";
const std::string GameOverState::SCORE_LABEL = "TOTAL SCORE: ";
const std::string GameOverState::RESTART_TEXT = "RESTART";
const std::string GameOverState::MENU_TEXT = "MENU";

GameOverState::GameOverState(Game& game)
	: GameState(game), 
	levelLoader(game.getLevelLoader()),
	restartButton(game.getSoundPlayer()),
	menuButton(game.getSoundPlayer())
{
	valueGetter.attachLevelDataObserver(this);
}


void GameOverState::init()
{
	setBackground(valueGetter.getGeneralAsset(GAME_OVER_IMAGE));
}

void GameOverState::onStateEnter()
{
	totalScoreText->setString(SCORE_LABEL + std::to_string(totalScore));
	audioPlayer.loadPlayMusic(AudioType::GAME_OVER_MUSIC);
}

void GameOverState::handleInput(sf::Event& event)
{
	if (restartButton.buttonInteract(window, event))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::PLAYING_STATE;
		levelLoader.setLevel(currentMode);
	}

	if (menuButton.buttonInteract(window, event))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::MAIN_MENU;
		levelLoader.setLevel(currentMode);
		displayLoading();

		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::MAIN_MENU);
	}
}

void GameOverState::draw()
{
	window.draw(bgImage);
	window.draw(*gameOverText);
	window.draw(*totalScoreText);

	for (Button& button : buttons)
		button.drawButton(window);
}

void GameOverState::onStateExit()
{
	totalScore = 0;
	audioPlayer.stopMusic();
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
		displayLoading();

		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::PLAYING_STATE);
	}
}

void GameOverState::setTextElements()
{
	float gameOverTextSize = window.getSize().y * gameOverTextPercentage / 100.0f;
	float scoreTextSize = window.getSize().y * scoreTextPercentage / 100.0f;
	float topOffset = window.getSize().y * gameOverTextTopOffsetPercentage / 100.0f;
	float verticalTextSpacing = window.getSize().y * verticalTextSpacingPercentage / 100.0f;

	TextCreator textCreator(topOffset, 0);
	gameOverText = textCreator.createNewText(window, font, GAME_OVER_LABEL, TextAlignment::TOP_CENTER, gameOverTextSize);
	gameOverText->setFillColor(textColor);

	Vector2f posBelowGameOverText = gameOverText->getPosition() + Vector2f(0, gameOverText->getLocalBounds().height + verticalTextSpacing);
	totalScoreText = textCreator.createNewText(font, SCORE_LABEL + std::to_string(totalScore), posBelowGameOverText, scoreTextSize, TextOrigin::TOP_CENTER);
	totalScoreText->setFillColor(textColor);
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

	restartButton.setButtonText(RESTART_TEXT);
	menuButton.setButtonText(MENU_TEXT);

	restartButton.setButtonPosition(restartButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(menuButtonPosition, buttonTextOffset);

	for (Button& button : buttons)
	{
		button.configureButton(buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
		button.setButtonOutline(1.0f, buttonTextColor);
	}
}

void GameOverState::update(float deltaTime) {}
void GameOverState::attachValueObserver(HUDObserver* observer) {}
