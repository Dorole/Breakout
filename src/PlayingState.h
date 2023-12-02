#pragma once
#include "GameState.h"
#include <vector>
#include <SFML/Graphics.hpp>

#include "ValueGetter.h"
#include "BrickGrid.h"
#include "BrickObserver.h"
#include "GameObject.h"
#include "NumValueObserver.h"

class PlayingState : public GameState, public BrickObserver, public NumValueObserver
{
private:

	BrickGrid& grid;

	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<NumValueObserver*> observers;

	int totalScore = 0;
	int maxLives = 3; //to gameConfig
	int currentLives = maxLives;

	bool gameStarted = false;

	void startGame();
	void restartGame();
	void updateScore(int amount);
	void updateLives(int amount);

public:
	PlayingState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef);

	void init();
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void cleanup() override;


	virtual void attachObserver(NumValueObserver* observer) override;

	void onBrickDestroyed(Brick& brick) override;
	void onValueChanged(int value, ValueType valueType) override;

};

//mozda da salje u Game ili nekamo, i onda od tamo u UI?
//unsubscribe