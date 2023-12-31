#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "ValueGetter.h"
#include "LevelLoader.h"
#include "MusicPlayer.h"
#include "BrickGrid.h"
#include "GameState.h"
#include "NumValueObserver.h"
#include "StateObserver.h"



using namespace sf;

class Game : public NumValueObserver, public StateObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;
	LevelLoader& levelLoader;
	MusicPlayer& audioPlayer;

	std::shared_ptr<GameState> currentState;
	std::vector<NumValueObserver*> observers; 

	std::shared_ptr<GameState> mainMenuState;
	std::shared_ptr<GameState> playingState;
	std::shared_ptr<GameState> gameOverState;
	std::shared_ptr<GameState> levelClearState;

	bool hasSwitched = false;

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& grid, LevelLoader& levelLoaderRef, MusicPlayer& audioPlayerRef);

	void changeState(std::shared_ptr<GameState> newState);
	void handleInput();
	void update(float deltaTime);
	void draw();

	void attachObserver(NumValueObserver* observer);
	void onValueChanged(int value, ValueType valueType) override;
	void onStateChanged(State state) override;
};


