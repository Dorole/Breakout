#include "LoadingScreen.h"

const std::string LoadingScreen::LOADING_TEXT = "LOADING...";

LoadingScreen::LoadingScreen(sf::RenderWindow& windowRef) : window(windowRef) {}

void LoadingScreen::setText(sf::Font& font, const sf::Color& textColor)
{
	float titleTextSize = window.getSize().y * 20.0f / 100.0f;
	Vector2f position = Vector2f(window.getSize().x / 2, window.getSize().y / 2);

	TextCreator textCreator(0, 0);
	loadingText = textCreator.createNewText(font, LOADING_TEXT, position, titleTextSize, TextOrigin::CENTER);
	loadingText->setFillColor(textColor);
}

void LoadingScreen::displayLoading(sf::Font& font, const sf::Color& textColor)
{
	setText(font, textColor);

	window.clear();
	loadingText->setFont(font);
	window.draw(*loadingText);
	window.display();
}