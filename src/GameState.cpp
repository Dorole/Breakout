#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ValueGetter.h"


GameState::GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef)
	: window(windowRef), valueGetter(valueGetterRef)
{
	std::cout << "GameState non empty constructor" << std::endl;
	baseInit();
}


void GameState::baseInit()
{
	std::cout << "GameState base init" << std::endl;
	//init stuff common to all game states
}