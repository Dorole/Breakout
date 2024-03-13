#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "LevelLoader.h"
#include "MusicPlayer.h"
#include "BrickGrid.h"

using namespace sf;

class Game 
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;
	LevelLoader& levelLoader;
	MusicPlayer& audioPlayer;

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef, LevelLoader& levelLoaderRef, MusicPlayer& audioPlayerRef);

	RenderWindow& getWindow() const { return window; }
	ValueGetter& getValueGetter() const { return valueGetter; }
	LevelLoader& getLevelLoader() const { return levelLoader; }
	MusicPlayer& getMusicPlayer() const { return audioPlayer; }
	BrickGrid& getGrid() const { return grid; }
};


