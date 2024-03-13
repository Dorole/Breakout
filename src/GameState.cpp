#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Game.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"

GameState::GameState(Game& gameRef)
	: window(gameRef.getWindow()), valueGetter(gameRef.getValueGetter()), audioPlayer(gameRef.getMusicPlayer())
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