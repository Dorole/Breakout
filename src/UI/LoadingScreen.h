#pragma once
#include <SFML/Graphics.hpp>
#include "TextCreator.h"

class LoadingScreen
{
private:
	sf::RenderWindow& window;

	std::unique_ptr<Text> loadingText;
	static const std::string LOADING_TEXT;

	void setText(sf::Font& font, const sf::Color& textColor);

public:
	LoadingScreen(sf::RenderWindow& windowRef);

	void displayLoading(sf::Font& font, const sf::Color& textColor);
};