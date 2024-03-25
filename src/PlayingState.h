#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameState.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "BrickGrid.h"
#include "GameObject.h"
#include "BrickObserver.h"
#include "UIManager.h"
#include "NumValueObserver.h"
#include "StateObserver.h"
#include "CollisionManager.h"

class PlayingState : public GameState, public BrickObserver, public NumValueObserver
{
private:

	BrickGrid& grid;
	CollisionManager& colMan;
	std::unique_ptr<UIManager> uiManager;

	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<NumValueObserver*> valueObservers;
	std::vector<StateObserver*> stateObservers;

	int totalScore = 0;
	int maxLives = 3; 
	int currentLives = maxLives;

	bool gameStarted = false;

	void startGame();
	void restartGame();
	void updateScore(int amount);
	void updateLives(int amount);

public:
	PlayingState(Game& game);

	void init(Game& game);

	// Inherited via GameState
	virtual void onStateEnter() override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void setTextElements() override;
	virtual void setButtonElements() override;
	virtual void attachValueObserver(NumValueObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;

	// Inherited via BrickObserver
	void onBrickDestroyed(Brick& brick) override;

	// Inherited via NumValueObserver
	void onValueChanged(int value, ValueType valueType) override;
};

