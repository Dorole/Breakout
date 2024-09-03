#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameState.h"
#include "BrickGrid.h"
#include "utils/ValueGetter.h"
#include "audio/MusicPlayer.h"
#include "objects/GameObject.h"
#include "objects/Ball.h"
#include "ui/UIManager.h"
#include "events/BrickObserver.h"
#include "events/HUDObserver.h"
#include "events/StateObserver.h"
#include "events/InteractionObserver.h"
#include "collision/CollisionManager.h"


class PlayingState : public GameState, public BrickObserver, public HUDObserver, public InteractionObserver
{
private:

	Game& game;
	BrickGrid& grid;
	CollisionManager& collisionManager;

	std::unique_ptr<UIManager> uiManager;
	Ball* ball = nullptr;
	std::vector<std::unique_ptr<GameObject>> gameObjects;  

	std::vector<HUDObserver*> valueObservers;
	std::vector<StateObserver*> stateObservers;

	int totalScore = 0;
	int maxLives = 3;
	int currentLives = maxLives;

	bool gameStarted = false;
	bool paused = false;

	void startGame();
	void restartGame();
	void updateScore(int amount);
	void updateLives(int amount);
	void handlePause();
	void handleLostLife(int value);
	void updateGameObjects(float deltaTime);
	void checkForStateExit();

public:
	PlayingState(Game& gameRef);

	// Inherited via GameState
	virtual void init() override;
	virtual void onStateEnter() override;
	virtual void handleInput(sf::Event& event) override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void setTextElements() override;
	virtual void setButtonElements() override;
	virtual void attachValueObserver(HUDObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;

	// Inherited via BrickObserver
	void onBrickDestroyed(Brick& brick) override;

	// Inherited via HUDObserver
	void onValueChanged(int value, ValueType valueType) override;

	// Inherited via InteractionObserver
	virtual void onInteract(InteractionType interactionType) override;
};



