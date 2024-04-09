#include "Game.h"

using namespace sf;

Game::Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef, LevelLoader& levelLoaderRef, 
	MusicPlayer& audioPlayerRef, CollisionManager& collisionManagerRef, LevelDataProvider& levelDataProviderRef)
	: window(windowRef), valueGetter(valueGetterRef), grid (gridRef), levelLoader(levelLoaderRef), 
	audioPlayer(audioPlayerRef), collisionManager(collisionManagerRef), levelDataProvider(levelDataProviderRef)
{
	
}



