#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ValueGetter.h"

GameState::GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef)
	: window(windowRef), valueGetter(valueGetterRef)
{
	baseInit();
}


void GameState::baseInit()
{
	//init stuff common to all game states
}