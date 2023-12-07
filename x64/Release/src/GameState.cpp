#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"

GameState::GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, MusicPlayer& audioPlayerRef)
	: window(windowRef), valueGetter(valueGetterRef), audioPlayer(audioPlayerRef)
{
	baseInit();
}


void GameState::baseInit()
{
	//init stuff common to all game states
}

void GameState::setBackground(std::string texturePath)
{
	bgTexture.loadFromFile(texturePath);
	bgImage.setTexture(bgTexture);
	imageConfig.configureImage(window, bgTexture, bgImage);
}