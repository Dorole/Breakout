#include "LevelClearState.h"
#include "UI/TextCreator.h"

const std::string LevelClearState::LEVEL_CLEAR_IMAGE = "LevelClearImage";
const std::string LevelClearState::LEVEL_CLEAR_LABEL = "LEVEL CLEAR!";
const std::string LevelClearState::GAME_CLEAR_LABEL = "GAME CLEAR!";
const std::string LevelClearState::SCORE_LABEL = "TOTAL SCORE: ";
const std::string LevelClearState::RESTART_TEXT = "RESTART";
const std::string LevelClearState::NEXT_TEXT = "NEXT";
const std::string LevelClearState::MENU_TEXT = "MENU";

LevelClearState::LevelClearState(Game& game)
	: GameState(game), 
	levelLoader(game.getLevelLoader()),
	nextButton(game.getSoundPlayer()),
	restartButton(game.getSoundPlayer()),
	menuButton(game.getSoundPlayer())
{
	valueGetter.attachLevelDataObserver(this);
}

void LevelClearState::init()
{
	setBackground(valueGetter.getGeneralAsset(LEVEL_CLEAR_IMAGE));
}

void LevelClearState::onStateEnter()
{
	totalScoreText->setString(SCORE_LABEL + std::to_string(totalScore));

	if (levelLoader.nextLevelExists())
		audioPlayer.loadPlayMusic(AudioType::LEVEL_CLEAR_MUSIC);
	else
	{
		levelClearText->setString(GAME_CLEAR_LABEL);
		audioPlayer.loadPlayMusic(AudioType::GAME_FINISHED_MUSIC);
		nextButton.setVisibility(false);
	}
}

void LevelClearState::handleInput(Event& event)
{
	if (nextButton.buttonInteract(window, event))
	{
		currentMode = LoadLevelMode::PROGRESS;
		nextState = State::PLAYING_STATE;
		levelLoader.setLevel(currentMode);
	}

	if (restartButton.buttonInteract(window, event))
	{
		currentMode = LoadLevelMode::RESET_LEVEL;
		nextState = State::PLAYING_STATE;
		levelLoader.setLevel(currentMode);
	}

	if (menuButton.buttonInteract(window, event))
	{
		if (levelLoader.nextLevelExists())
			currentMode = LoadLevelMode::RESET_LEVEL;
		else
			currentMode = LoadLevelMode::RESET_GAME;

		nextState = State::MAIN_MENU;
		levelLoader.setLevel(currentMode);
	}
}

void LevelClearState::draw()
{
	window.draw(bgImage);

	window.draw(*levelClearText);
	window.draw(*totalScoreText);

	if (levelLoader.nextLevelExists())
		nextButton.drawButton(window);

	restartButton.drawButton(window);
	menuButton.drawButton(window);
}

void LevelClearState::onStateExit()
{
	totalScore = 0;
	audioPlayer.stopMusic();
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
	displayLoading();

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

void LevelClearState::setTextElements()
{
	float levelClearTextSize = window.getSize().y * levelClearTextPercentage / 100.0f;
	float scoreTextSize = window.getSize().y * scoreTextPercentage / 100.0f;
	float topOffset = window.getSize().y * levelClearTopOffsetPercentage / 100.0f;
	float verticalTextSpacing = window.getSize().y * verticalTextSpacingPercentage / 100.0f;

	TextCreator textCreator(30, 0);
	levelClearText = textCreator.createNewText(window, font, LEVEL_CLEAR_LABEL, TextAlignment::TOP_CENTER, levelClearTextSize);

	Vector2f posBelowGameOverText = levelClearText->getPosition() + Vector2f(0, levelClearText->getLocalBounds().height + verticalTextSpacing);
	totalScoreText = textCreator.createNewText(font, SCORE_LABEL + std::to_string(totalScore), posBelowGameOverText, scoreTextSize, TextOrigin::TOP_CENTER);
	totalScoreText->setFillColor(textColor);
	totalScoreText->setOutlineThickness(outlineThickness);
	totalScoreText->setOutlineColor(outlineColor);
}

void LevelClearState::setButtonElements()
{
	float buttonWidth = window.getSize().x * buttonWidthPercentage / 100.0f;
	float buttonHeight = window.getSize().y * buttonHeightPercentage / 100.0f;
	Vector2f buttonSize = Vector2f(buttonWidth, buttonHeight);

	float buttonTextSize = buttonHeight * buttonTextSizePercentage / 100.0f;

	float buttonSpacing = window.getSize().y * buttonSpacingPercentage / 100.0f;

	Vector2f nextButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
	Vector2f restartButtonPosition = Vector2f(window.getSize().x / 2.0f, nextButtonPosition.y + buttonSize.y + buttonSpacing);
	Vector2f menuButtonPosition = Vector2f(window.getSize().x / 2.0f, restartButtonPosition.y + buttonSize.y + buttonSpacing);

	nextButton.setButtonText(NEXT_TEXT);
	restartButton.setButtonText(RESTART_TEXT);
	menuButton.setButtonText(MENU_TEXT);

	nextButton.setButtonPosition(nextButtonPosition, buttonTextOffset);
	restartButton.setButtonPosition(restartButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(menuButtonPosition, buttonTextOffset);

	for (Button& button : buttons)
	{
		button.configureButton(buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
		button.setButtonOutline(1.0f, buttonTextColor);
	}
}

void LevelClearState::update(float deltaTime) {}
void LevelClearState::attachValueObserver(HUDObserver* observer) {}
