#pragma once
#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "BrickGrid.h"
#include "LevelDataProvider.h"
#include "audio/MusicPlayer.h"
#include "audio/SoundPlayer.h"
#include "collision/CollisionManager.h"
#include "utils/ValueGetter.h"
#include "UI/ThemeManager.h"

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	LevelLoader levelLoader;
	ValueGetter valueGetter;
	MusicPlayer audioPlayer;
	SoundPlayer soundPlayer;
	CollisionManager collisionManager;
	ThemeManager themeManager;
	LevelDataProvider levelDataProvider;
	BrickPool pool;
	BrickGrid grid;


public:
	Game(RenderWindow& windowRef);

	RenderWindow& getWindow() const { return window; }
	ValueGetter& getValueGetter() { return valueGetter; }
	LevelLoader& getLevelLoader() { return levelLoader; }
	MusicPlayer& getMusicPlayer() { return audioPlayer; }
	SoundPlayer& getSoundPlayer() { return soundPlayer; }
	BrickPool& getBrickPool() { return pool; }
	BrickGrid& getGrid() { return grid; }
	CollisionManager& getCollisionManager() { return collisionManager; }
	LevelDataProvider& getLevelDataProvider() { return levelDataProvider; }
	ThemeManager& getThemeManager() { return themeManager; }
};




