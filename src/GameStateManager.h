#pragma once
#include "GameState.h"
#include "Game.h"
#include "NumValueObserver.h"
#include "StateObserver.h"

using namespace sf;

class GameStateManager : public NumValueObserver, public StateObserver
{
private:
	std::shared_ptr<GameState> currentState;
	std::vector<NumValueObserver*> observers;

	std::shared_ptr<GameState> mainMenuState;
	std::shared_ptr<GameState> playingState;
	std::shared_ptr<GameState> gameOverState;
	std::shared_ptr<GameState> levelClearState;

	bool hasSwitched = false;

public:
	GameStateManager(Game& game);

	void changeState(std::shared_ptr<GameState> newState);
	void handleInput();
	void update(float deltaTime);
	void draw();

	void attachObserver(NumValueObserver* observer);
	void onValueChanged(int value, ValueType valueType) override;
	void onStateChanged(State state) override;
};

