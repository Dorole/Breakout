#include "MainMenuState.h"
#include <functional>
#include "UI/TextCreator.h"

const std::string MainMenuState::GAME_TITLE = "BREAKOUT";
const std::string MainMenuState::MAIN_MENU_IMAGE_PATH = "MainMenuImage";
const std::string MainMenuState::START_TEXT = "START";
const std::string MainMenuState::QUIT_TEXT = "QUIT";
const std::string MainMenuState::SOUND_ON = "SOUND ON";
const std::string MainMenuState::SOUND_OFF = "SOUND OFF";

MainMenuState::MainMenuState(Game& game)
	: GameState(game), 
	startButton(game.getSoundPlayer()),
	quitButton(game.getSoundPlayer()),
	soundButton(game.getSoundPlayer())
{
	attachInteractionObserver(&game.getMusicPlayer());
	attachInteractionObserver(&game.getSoundPlayer());
}

void MainMenuState::init()
{
	setBackground(valueGetter.getGeneralAsset(MAIN_MENU_IMAGE_PATH));
}

void MainMenuState::onStateEnter()
{
	audioPlayer.loadPlayMusic(AudioType::MAIN_MENU_MUSIC);
}

void MainMenuState::handleInput(sf::Event& event)
{
	if (startButton.buttonInteract(window, event))
	{
		displayLoading();

		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::PLAYING_STATE);
	}

	if (soundButton.buttonInteract(window, event))
	{
		std::string buttonText = toggleSound();
		soundButton.setButtonText(buttonText);

		for (const auto& observer : interactionObservers)
			observer->onInteract(InteractionType::SOUND);
	}

	if (quitButton.buttonInteract(window, event))
	{
		window.close();
	}
}

void MainMenuState::draw()
{
	window.draw(bgImage);
	window.draw(*titleText);

	for (Button& button : buttons)
		button.drawButton(window);
}

void MainMenuState::onStateExit()
{
	audioPlayer.stopMusic();
}

void MainMenuState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}

void MainMenuState::setTextElements()
{
	float titleTextSize = window.getSize().y * titleTextSizePercentage / 100.0f;
	float topOffset = window.getSize().y * titleTextTopOffsetPercentage / 100.0f;

	TextCreator textCreator(topOffset, 0);
	titleText = textCreator.createNewText(window, font, GAME_TITLE, TextAlignment::TOP_CENTER, titleTextSize);
	titleText->setFillColor(titleColor);
}

void MainMenuState::setButtonElements()
{
	float buttonWidth = window.getSize().x * buttonWidthPercentage / 100.0f;
	float buttonHeight = window.getSize().y * buttonHeightPercentage / 100.0f;
	Vector2f buttonSize = Vector2f(buttonWidth, buttonHeight);

	float buttonTextSize = buttonHeight * buttonTextSizePercentage / 100.0f;

	float buttonSpacing = window.getSize().y * buttonSpacingPercentage / 100.0f;
	Vector2f startButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
	Vector2f soundButtonPosition = Vector2f(window.getSize().x / 2.0f, startButtonPosition.y + buttonSize.y + buttonSpacing);
	Vector2f quitButtonPosition = Vector2f(window.getSize().x / 2.0f, soundButtonPosition.y + buttonSize.y + buttonSpacing);

	startButton.setButtonText(START_TEXT);
	soundButton.setButtonText(SOUND_ON);
	quitButton.setButtonText(QUIT_TEXT);

	startButton.setButtonPosition(startButtonPosition, buttonTextOffset);
	soundButton.setButtonPosition(soundButtonPosition, buttonTextOffset);
	quitButton.setButtonPosition(quitButtonPosition, buttonTextOffset);

	for (Button& button : buttons)
	{
		button.configureButton(buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
		button.setButtonOutline(1.0f, buttonTextColor);
	}
}

std::string MainMenuState::toggleSound()
{
	isSoundOn = !isSoundOn;
	return isSoundOn ? SOUND_ON : SOUND_OFF;
}

void MainMenuState::attachInteractionObserver(InteractionObserver* observer)
{
	interactionObservers.push_back(observer);
}

void MainMenuState::update(float deltaTime) {}
void MainMenuState::attachValueObserver(HUDObserver* observer) {}