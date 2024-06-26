#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "LevelLoader.h"
#include "MusicPlayer.h"
#include "BrickGrid.h"
#include "CollisionManager.h"
#include "LevelDataProvider.h"

using namespace sf;

class Game 
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;
	LevelLoader& levelLoader;
	MusicPlayer& audioPlayer;
	CollisionManager& collisionManager;
	LevelDataProvider& levelDataProvider;

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef, LevelLoader& levelLoaderRef, 
		MusicPlayer& audioPlayerRef, CollisionManager& collisionManagerRef, LevelDataProvider& levelDataProviderRef);

	RenderWindow& getWindow() const { return window; }
	ValueGetter& getValueGetter() const { return valueGetter; }
	LevelLoader& getLevelLoader() const { return levelLoader; }
	MusicPlayer& getMusicPlayer() const { return audioPlayer; }
	BrickGrid& getGrid() const { return grid; }
	CollisionManager& getCollisionManager() const { return collisionManager; }
	LevelDataProvider& getLevelDataProvider() const { return levelDataProvider; }
};


