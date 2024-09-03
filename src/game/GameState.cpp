#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Game.h"

const std::string GameState::FONT_PATH = "ThemeFont";

GameState::GameState(Game& gameRef)
	: window(gameRef.getWindow()), valueGetter(gameRef.getValueGetter()), audioPlayer(gameRef.getMusicPlayer()),
	themeManager(gameRef.getThemeManager()), loadingScreen(gameRef.getWindow())
{
	valueGetter.attachInitReadyObserver(this);
}

void GameState::setBackground(std::string texturePath)
{
	bgTexture.loadFromFile(texturePath);
	bgImage.setTexture(bgTexture);
	imageConfig.configureImage(window, bgTexture, bgImage);
}

void GameState::updateThematicElements()
{
	font.loadFromFile(valueGetter.getGeneralAsset(FONT_PATH));

	const ThemeData& theme = themeManager.getCurrentTheme();
	buttonColor = theme.buttonColor;
	buttonTextColor = theme.buttonTextColor;
	textColor = theme.textColor;
	hudColor = theme.hudColor;
	titleColor = theme.titleColor;
	outlineColor = theme.outlineColor;
	outlineThickness = theme.outlineThickness;

}

void GameState::onInit()
{
	updateThematicElements();
	setTextElements();
	setButtonElements();

	init();
}

void GameState::displayLoading()
{
	loadingScreen.displayLoading(font, textColor);
}
