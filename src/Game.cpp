#include "Game.h"
#include <SFML/Graphics.hpp>

#include "ValueGetter.h"
#include "BrickGrid.h"
#include "LevelLoader.h"
#include "MusicPlayer.h"


using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef, LevelLoader& levelLoaderRef, MusicPlayer& audioPlayerRef)
	: window(windowRef), valueGetter(valueGetterRef), grid (gridRef), levelLoader(levelLoaderRef), audioPlayer(audioPlayerRef)
{
	
}



