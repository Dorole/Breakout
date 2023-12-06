#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ValueGetter.h"
#include "AudioPlayer.h"

GameState::GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, AudioPlayer& audioPlayerRef)
	: window(windowRef), valueGetter(valueGetterRef), audioPlayer(audioPlayerRef)
{
	baseInit();
}


void GameState::baseInit()
{
	//init stuff common to all game states
}