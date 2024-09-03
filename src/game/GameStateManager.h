#pragma once
#include "GameState.h"
#include "Game.h"
#include "events/HUDObserver.h"
#include "events/StateObserver.h"
#include "events/ThemeSelectionObserver.h"

using namespace sf;

class GameStateManager : public HUDObserver, public StateObserver
{
private:
	std::shared_ptr<GameState> currentState;
	std::vector<HUDObserver*> observers;

	std::shared_ptr<GameState> themeSelectionState;
	std::shared_ptr<GameState> mainMenuState;
	std::shared_ptr<GameState> playingState;
	std::shared_ptr<GameState> gameOverState;
	std::shared_ptr<GameState> levelClearState;

	void checkSkipGameplay();

public:
	GameStateManager(Game& game);

	void changeState(std::shared_ptr<GameState> newState);
	void handleInput(Event& event);
	void update(float deltaTime);
	void draw();

	void attachObserver(HUDObserver* observer);
	void onValueChanged(int value, ValueType valueType) override;
	void onStateChanged(State state) override;
};


