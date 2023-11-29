#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "BrickGridVisual.h"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include "BrickObserver.h"
#include "NumValueObserver.h"

using namespace sf;

class Game : public BrickObserver, public NumValueObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;

	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<NumValueObserver*> uiObservers;

	int totalScore = 0;
	int maxLives = 3; //to gameConfig
	int currentLives = maxLives;

	bool gameStarted = false;

	void updateScore(int amount);
	void updateLives(int amount);

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& grid);

	void update(float deltaTime);
	void render();

	void startGame();
	void restartGame();

	int getScore() const;
	int getMaxLives() { return maxLives; }

	void attachObserver(NumValueObserver* observer);

	void onBrickDestroyed(Brick& brick) override;
	void onValueChanged(int value, ValueType valueType) override;
};


