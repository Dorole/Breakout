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

void MainMenuState::handleInput()
{
	if (startButton.isMouseOverButton(window))
	{
		startButton.setButtonTransparency(AlphaChannel::HALF_TRANSPARENT);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			std::cout << "StartButton pressed" << std::endl;
			for (const auto& observer : stateObservers)
				observer->onStateChanged(State::PLAYING_STATE);
		}
	}
	else
		startButton.setButtonTransparency(AlphaChannel::OPAQUE);
	
	if (quitButton.isMouseOverButton(window))
	{
		quitButton.setButtonTransparency(AlphaChannel::HALF_TRANSPARENT);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			std::cout << "QuitButton pressed" << std::endl;
			window.close();
		}
	}
	else
		quitButton.setButtonTransparency(AlphaChannel::OPAQUE);

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

void MainMenuState::cleanup()
{

}

void MainMenuState::attachValueObserver(NumValueObserver* observer)
{
}

void MainMenuState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}
