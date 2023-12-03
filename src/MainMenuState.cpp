#include "MainMenuState.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TextCreator.h"
#include "NumValueObserver.h"
#include "StateObserver.h"
#include "Button.h"

MainMenuState::MainMenuState(sf::RenderWindow& windowRef, ValueGetter& valueGetter)
	: GameState(windowRef, valueGetter)
{
	std::cout << "MainMenu state ctr" << std::endl;

	init();
}

void MainMenuState::init()
{
	font.loadFromFile("resources/fonts/Cartoon Blocks Christmas.otf"); //get iz gameConfig-a

	TextCreator textCreator(50, 0);
	titleText = textCreator.createNewText(window, font, "BREAKOUT", TextAlignment::TOP_CENTER, 100);

	startButton = Button(startText, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
	quitButton = Button(quitText, buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);

	startButton.setButtonPosition(startButtonPosition, buttonTextOffset);
	quitButton.setButtonPosition(quitButtonPosition, buttonTextOffset);

}

void MainMenuState::onStateEnter()
{
}

void MainMenuState::handleInput()
{
	if (startButton.buttonInteract(window))
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::PLAYING_STATE);
	}

	if (quitButton.buttonInteract(window))
	{
		window.close();
	}
}

void MainMenuState::update(float deltaTime)
{
}

void MainMenuState::draw()
{
	window.draw(*titleText);

	startButton.drawButton(window);
	quitButton.drawButton(window);
}

void MainMenuState::onStateExit()
{

}

void MainMenuState::attachValueObserver(NumValueObserver* observer)
{
}

void MainMenuState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}
